/*
 * Copyright (c) 1999-2001, 2003, PADL Software Pty Ltd.
 * Copyright (c) 2004-2009, Andrew Bartlett <abartlet@samba.org>.
 * Copyright (c) 2004, Stefan Metzmacher <metze@samba.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of PADL Software  nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY PADL SOFTWARE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL PADL SOFTWARE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include "includes.h"
#include "kdc/kdc-glue.h"
#include "kdc/db-glue.h"
#include "auth/auth_sam.h"
#include "auth/common_auth.h"
#include <ldb.h>
#include "sdb.h"
#include "sdb_hdb.h"
#include "dsdb/samdb/samdb.h"
#include "param/param.h"
#include "../lib/tsocket/tsocket.h"
#include "librpc/gen_ndr/ndr_winbind_c.h"
#include "lib/messaging/irpc.h"

static krb5_error_code hdb_samba4_open(krb5_context context, HDB *db, int flags, mode_t mode)
{
	if (db->hdb_master_key_set) {
		krb5_error_code ret = HDB_ERR_NOENTRY;
		krb5_warnx(context, "hdb_samba4_open: use of a master key incompatible with LDB\n");
		krb5_set_error_message(context, ret, "hdb_samba4_open: use of a master key incompatible with LDB\n");
		return ret;
	}

	return 0;
}

static krb5_error_code hdb_samba4_close(krb5_context context, HDB *db)
{
	return 0;
}

static krb5_error_code hdb_samba4_lock(krb5_context context, HDB *db, int operation)
{
	return 0;
}

static krb5_error_code hdb_samba4_unlock(krb5_context context, HDB *db)
{
	return 0;
}

static krb5_error_code hdb_samba4_rename(krb5_context context, HDB *db, const char *new_name)
{
	return HDB_ERR_DB_INUSE;
}

static krb5_error_code hdb_samba4_store(krb5_context context, HDB *db, unsigned flags, hdb_entry_ex *entry)
{
	return HDB_ERR_DB_INUSE;
}

static krb5_error_code hdb_samba4_remove(krb5_context context, HDB *db, krb5_const_principal principal)
{
	return HDB_ERR_DB_INUSE;
}

static krb5_error_code hdb_samba4_fetch_kvno(krb5_context context, HDB *db,
					     krb5_const_principal principal,
					     unsigned flags,
					     krb5_kvno kvno,
					     hdb_entry_ex *entry_ex)
{
	struct samba_kdc_db_context *kdc_db_ctx;
	struct sdb_entry_ex sdb_entry_ex = {};
	krb5_error_code code, ret;

	kdc_db_ctx = talloc_get_type_abort(db->hdb_db,
					   struct samba_kdc_db_context);

	ret = samba_kdc_fetch(context,
			      kdc_db_ctx,
			      principal,
			      flags,
			      kvno,
			      &sdb_entry_ex);
	switch (ret) {
	case 0:
		code = 0;
		break;
	case SDB_ERR_WRONG_REALM:
		/*
		 * If SDB_ERR_WRONG_REALM is returned we need to process the
		 * sdb_entry to fill the principal in the HDB entry.
		 */
		code = HDB_ERR_WRONG_REALM;
		break;
	case SDB_ERR_NOENTRY:
		return HDB_ERR_NOENTRY;
	case SDB_ERR_NOT_FOUND_HERE:
		return HDB_ERR_NOT_FOUND_HERE;
	default:
		return ret;
	}

	ret = sdb_entry_ex_to_hdb_entry_ex(context, &sdb_entry_ex, entry_ex);
	sdb_free_entry(&sdb_entry_ex);

	if (code != 0 && ret != 0) {
		code = ret;
	}

	return code;
}

static krb5_error_code hdb_samba4_kpasswd_fetch_kvno(krb5_context context, HDB *db,
						     krb5_const_principal _principal,
						     unsigned flags,
						     krb5_kvno _kvno,
						     hdb_entry_ex *entry_ex)
{
	struct samba_kdc_db_context *kdc_db_ctx = NULL;
	krb5_error_code ret;
	krb5_principal kpasswd_principal = NULL;

	kdc_db_ctx = talloc_get_type_abort(db->hdb_db,
					   struct samba_kdc_db_context);

	ret = smb_krb5_make_principal(context, &kpasswd_principal,
				      lpcfg_realm(kdc_db_ctx->lp_ctx),
				      "kadmin", "changepw",
				      NULL);
	if (ret) {
		return ret;
	}
	smb_krb5_principal_set_type(context, kpasswd_principal, KRB5_NT_SRV_INST);

	/*
	 * For the kpasswd service, always ensure we get the latest kvno. This
	 * also means we (correctly) refuse RODC-issued tickets.
	 */
	flags &= ~HDB_F_KVNO_SPECIFIED;

	/* Don't bother looking up a client or krbtgt. */
	flags &= ~(SDB_F_GET_CLIENT|SDB_F_GET_KRBTGT);

	ret = hdb_samba4_fetch_kvno(context, db,
				    kpasswd_principal,
				    flags,
				    0,
				    entry_ex);

	krb5_free_principal(context, kpasswd_principal);
	return ret;
}

static krb5_error_code hdb_samba4_firstkey(krb5_context context, HDB *db, unsigned flags,
					hdb_entry_ex *entry)
{
	struct samba_kdc_db_context *kdc_db_ctx;
	struct sdb_entry_ex sdb_entry_ex = {};
	krb5_error_code ret;

	kdc_db_ctx = talloc_get_type_abort(db->hdb_db,
					   struct samba_kdc_db_context);

	ret = samba_kdc_firstkey(context, kdc_db_ctx, &sdb_entry_ex);
	switch (ret) {
	case 0:
		break;
	case SDB_ERR_WRONG_REALM:
		return HDB_ERR_WRONG_REALM;
	case SDB_ERR_NOENTRY:
		return HDB_ERR_NOENTRY;
	case SDB_ERR_NOT_FOUND_HERE:
		return HDB_ERR_NOT_FOUND_HERE;
	default:
		return ret;
	}

	ret = sdb_entry_ex_to_hdb_entry_ex(context, &sdb_entry_ex, entry);
	sdb_free_entry(&sdb_entry_ex);
	return ret;
}

static krb5_error_code hdb_samba4_nextkey(krb5_context context, HDB *db, unsigned flags,
				   hdb_entry_ex *entry)
{
	struct samba_kdc_db_context *kdc_db_ctx;
	struct sdb_entry_ex sdb_entry_ex = {};
	krb5_error_code ret;

	kdc_db_ctx = talloc_get_type_abort(db->hdb_db,
					   struct samba_kdc_db_context);

	ret = samba_kdc_nextkey(context, kdc_db_ctx, &sdb_entry_ex);
	switch (ret) {
	case 0:
		break;
	case SDB_ERR_WRONG_REALM:
		return HDB_ERR_WRONG_REALM;
	case SDB_ERR_NOENTRY:
		return HDB_ERR_NOENTRY;
	case SDB_ERR_NOT_FOUND_HERE:
		return HDB_ERR_NOT_FOUND_HERE;
	default:
		return ret;
	}

	ret = sdb_entry_ex_to_hdb_entry_ex(context, &sdb_entry_ex, entry);
	sdb_free_entry(&sdb_entry_ex);
	return ret;
}

static krb5_error_code hdb_samba4_nextkey_panic(krb5_context context, HDB *db,
						unsigned flags,
						hdb_entry_ex *entry)
{
	DBG_ERR("Attempt to iterate kpasswd keytab => PANIC\n");
	smb_panic("hdb_samba4_nextkey_panic: Attempt to iterate kpasswd keytab");
}

static krb5_error_code hdb_samba4_destroy(krb5_context context, HDB *db)
{
	talloc_free(db);
	return 0;
}

static krb5_error_code
hdb_samba4_check_constrained_delegation(krb5_context context, HDB *db,
					hdb_entry_ex *entry,
					krb5_const_principal target_principal)
{
	struct samba_kdc_db_context *kdc_db_ctx;
	struct samba_kdc_entry *skdc_entry;
	krb5_error_code ret;

	kdc_db_ctx = talloc_get_type_abort(db->hdb_db,
					   struct samba_kdc_db_context);
	skdc_entry = talloc_get_type_abort(entry->ctx,
					   struct samba_kdc_entry);

	ret = samba_kdc_check_s4u2proxy(context, kdc_db_ctx,
					skdc_entry,
					target_principal);
	switch (ret) {
	case 0:
		break;
	case SDB_ERR_WRONG_REALM:
		ret = HDB_ERR_WRONG_REALM;
		break;
	case SDB_ERR_NOENTRY:
		ret = HDB_ERR_NOENTRY;
		break;
	case SDB_ERR_NOT_FOUND_HERE:
		ret = HDB_ERR_NOT_FOUND_HERE;
		break;
	default:
		break;
	}

	return ret;
}

static krb5_error_code
hdb_samba4_check_pkinit_ms_upn_match(krb5_context context, HDB *db,
				     hdb_entry_ex *entry,
				     krb5_const_principal certificate_principal)
{
	struct samba_kdc_db_context *kdc_db_ctx;
	struct samba_kdc_entry *skdc_entry;
	krb5_error_code ret;

	kdc_db_ctx = talloc_get_type_abort(db->hdb_db,
					   struct samba_kdc_db_context);
	skdc_entry = talloc_get_type_abort(entry->ctx,
					   struct samba_kdc_entry);

	ret = samba_kdc_check_pkinit_ms_upn_match(context, kdc_db_ctx,
						  skdc_entry,
						  certificate_principal);
	switch (ret) {
	case 0:
		break;
	case SDB_ERR_WRONG_REALM:
		ret = HDB_ERR_WRONG_REALM;
		break;
	case SDB_ERR_NOENTRY:
		ret = HDB_ERR_NOENTRY;
		break;
	case SDB_ERR_NOT_FOUND_HERE:
		ret = HDB_ERR_NOT_FOUND_HERE;
		break;
	default:
		break;
	}

	return ret;
}

static krb5_error_code
hdb_samba4_check_s4u2self(krb5_context context, HDB *db,
			  hdb_entry_ex *client_entry,
			  hdb_entry_ex *server_target_entry)
{
	struct samba_kdc_entry *skdc_client_entry
		= talloc_get_type_abort(client_entry->ctx,
					struct samba_kdc_entry);
	struct samba_kdc_entry *skdc_server_target_entry
		= talloc_get_type_abort(server_target_entry->ctx,
					struct samba_kdc_entry);

	return samba_kdc_check_s4u2self(context,
					skdc_client_entry,
					skdc_server_target_entry);
}

static void reset_bad_password_netlogon(TALLOC_CTX *mem_ctx,
					struct samba_kdc_db_context *kdc_db_ctx,
					struct netr_SendToSamBase *send_to_sam)
{
	struct dcerpc_binding_handle *irpc_handle;
	struct winbind_SendToSam req;

	irpc_handle = irpc_binding_handle_by_name(mem_ctx, kdc_db_ctx->msg_ctx,
						  "winbind_server",
						  &ndr_table_winbind);

	if (irpc_handle == NULL) {
		DEBUG(0, ("No winbind_server running!\n"));
		return;
	}

	req.in.message = *send_to_sam;

	dcerpc_winbind_SendToSam_r_send(mem_ctx, kdc_db_ctx->ev_ctx,
					irpc_handle, &req);
}

static krb5_error_code hdb_samba4_auth_status(krb5_context context, HDB *db,
					      hdb_entry_ex *entry,
					      struct sockaddr *from_addr,
					      struct timeval *start_time,
					      const char *original_client_name,
					      const char *auth_type,
					      int hdb_auth_status)
{
	struct samba_kdc_db_context *kdc_db_ctx = talloc_get_type_abort(db->hdb_db,
									struct samba_kdc_db_context);

	struct ldb_dn *domain_dn = ldb_get_default_basedn(kdc_db_ctx->samdb);
	uint64_t logon_id = generate_random_u64();

	/*
	 * Forcing this via the NTLM auth structure is not ideal, but
	 * it is the most practical option right now, and ensures the
	 * logs are consistent, even if some elements are always NULL.
	 */
	struct auth_usersupplied_info ui = {
		.was_mapped = true,
		.client = {
			.account_name = original_client_name,
			.domain_name = NULL,
		},
		.service_description = "Kerberos KDC",
		.auth_description = "ENC-TS Pre-authentication",
		.password_type = auth_type,
		.logon_id = logon_id
	};
	size_t sa_socklen = 0;
	int final_ret = 0;

	switch (from_addr->sa_family) {
	case AF_INET:
		sa_socklen = sizeof(struct sockaddr_in);
		break;
#ifdef HAVE_IPV6
	case AF_INET6:
		sa_socklen = sizeof(struct sockaddr_in6);
		break;
#endif
	}

	switch (hdb_auth_status) {
	case HDB_AUTHZ_SUCCESS:
	{
		TALLOC_CTX *frame = talloc_stackframe();
		struct samba_kdc_entry *p = talloc_get_type(entry->ctx,
							    struct samba_kdc_entry);
		struct netr_SendToSamBase *send_to_sam = NULL;

		/*
		 * TODO: We could log the AS-REQ authorization success here as
		 * well.  However before we do that, we need to pass
		 * in the PAC here or re-calculate it.
		 */
		authsam_logon_success_accounting(kdc_db_ctx->samdb, p->msg,
						 domain_dn, true, &send_to_sam);
		if (kdc_db_ctx->rodc && send_to_sam != NULL) {
			reset_bad_password_netlogon(frame, kdc_db_ctx, send_to_sam);
		}
		talloc_free(frame);
		break;
	}
	case HDB_AUTH_INVALID_SIGNATURE:
		break;
	case HDB_AUTH_CORRECT_PASSWORD:
	case HDB_AUTH_WRONG_PASSWORD:
	{
		TALLOC_CTX *frame = talloc_stackframe();
		struct samba_kdc_entry *p = talloc_get_type(entry->ctx,
							    struct samba_kdc_entry);
		struct dom_sid *sid
			= samdb_result_dom_sid(frame, p->msg, "objectSid");
		const char *account_name
			= ldb_msg_find_attr_as_string(p->msg, "sAMAccountName", NULL);
		const char *domain_name = lpcfg_sam_name(p->kdc_db_ctx->lp_ctx);
		struct tsocket_address *remote_host;
		NTSTATUS status;
		int ret;
		bool rwdc_fallback = false;

		ret = tsocket_address_bsd_from_sockaddr(frame, from_addr,
							sa_socklen,
							&remote_host);
		if (ret != 0) {
			ui.remote_host = NULL;
		} else {
			ui.remote_host = remote_host;
		}

		ui.mapped.account_name = account_name;
		ui.mapped.domain_name = domain_name;

		if (hdb_auth_status == HDB_AUTH_WRONG_PASSWORD) {
			authsam_update_bad_pwd_count(kdc_db_ctx->samdb, p->msg, domain_dn);
			status = NT_STATUS_WRONG_PASSWORD;
			rwdc_fallback = kdc_db_ctx->rodc;
		} else {
			status = NT_STATUS_OK;
		}

		if (rwdc_fallback) {
			/*
			 * Forward the request to an RWDC in order
			 * to give an authoritative answer to the client.
			 */
			ui.password_type = "Forwarding to RWDC";
			final_ret = HDB_ERR_NOT_FOUND_HERE;
		}

		log_authentication_event(kdc_db_ctx->msg_ctx,
					 kdc_db_ctx->lp_ctx,
					 start_time,
					 &ui,
					 status,
					 domain_name,
					 account_name,
					 sid);
		TALLOC_FREE(frame);
		break;
	}
	case HDB_AUTH_CLIENT_UNKNOWN:
	{
		struct tsocket_address *remote_host;
		int ret;
		TALLOC_CTX *frame = talloc_stackframe();
		ret = tsocket_address_bsd_from_sockaddr(frame, from_addr,
							sa_socklen,
							&remote_host);
		if (ret != 0) {
			ui.remote_host = NULL;
		} else {
			ui.remote_host = remote_host;
		}

		/* Note this is not forwarded to an RWDC */

		log_authentication_event(kdc_db_ctx->msg_ctx,
					 kdc_db_ctx->lp_ctx,
					 start_time,
					 &ui,
					 NT_STATUS_NO_SUCH_USER,
					 NULL, NULL,
					 NULL);
		TALLOC_FREE(frame);
		break;
	}
	}
	return final_ret;
}

/* This interface is to be called by the KDC and libnet_keytab_dump,
 * which is expecting Samba calling conventions.
 * It is also called by a wrapper (hdb_samba4_create) from the
 * kpasswdd -> krb5 -> keytab_hdb -> hdb code */

NTSTATUS hdb_samba4_create_kdc(struct samba_kdc_base_context *base_ctx,
			       krb5_context context, struct HDB **db)
{
	struct samba_kdc_db_context *kdc_db_ctx;
	NTSTATUS nt_status;

	if (hdb_interface_version != HDB_INTERFACE_VERSION) {
		krb5_set_error_message(context, EINVAL, "Heimdal HDB interface version mismatch between build-time and run-time libraries!");
		return NT_STATUS_ERROR_DS_INCOMPATIBLE_VERSION;
	}

	*db = talloc(base_ctx, HDB);
	if (!*db) {
		krb5_set_error_message(context, ENOMEM, "malloc: out of memory");
		return NT_STATUS_NO_MEMORY;
	}

	(*db)->hdb_master_key_set = 0;
	(*db)->hdb_db = NULL;
	(*db)->hdb_capability_flags = HDB_CAP_F_HANDLE_ENTERPRISE_PRINCIPAL;

	nt_status = samba_kdc_setup_db_ctx(*db, base_ctx, &kdc_db_ctx);
	if (!NT_STATUS_IS_OK(nt_status)) {
		talloc_free(*db);
		return nt_status;
	}
	(*db)->hdb_db = kdc_db_ctx;

	(*db)->hdb_dbc = NULL;
	(*db)->hdb_open = hdb_samba4_open;
	(*db)->hdb_close = hdb_samba4_close;
	(*db)->hdb_fetch_kvno = hdb_samba4_fetch_kvno;
	(*db)->hdb_store = hdb_samba4_store;
	(*db)->hdb_remove = hdb_samba4_remove;
	(*db)->hdb_firstkey = hdb_samba4_firstkey;
	(*db)->hdb_nextkey = hdb_samba4_nextkey;
	(*db)->hdb_lock = hdb_samba4_lock;
	(*db)->hdb_unlock = hdb_samba4_unlock;
	(*db)->hdb_rename = hdb_samba4_rename;
	/* we don't implement these, as we are not a lockable database */
	(*db)->hdb__get = NULL;
	(*db)->hdb__put = NULL;
	/* kadmin should not be used for deletes - use other tools instead */
	(*db)->hdb__del = NULL;
	(*db)->hdb_destroy = hdb_samba4_destroy;

	(*db)->hdb_auth_status = hdb_samba4_auth_status;
	(*db)->hdb_check_constrained_delegation = hdb_samba4_check_constrained_delegation;
	(*db)->hdb_check_pkinit_ms_upn_match = hdb_samba4_check_pkinit_ms_upn_match;
	(*db)->hdb_check_s4u2self = hdb_samba4_check_s4u2self;

	return NT_STATUS_OK;
}

NTSTATUS hdb_samba4_kpasswd_create_kdc(struct samba_kdc_base_context *base_ctx,
				       krb5_context context, struct HDB **db)
{
	NTSTATUS nt_status;

	nt_status = hdb_samba4_create_kdc(base_ctx, context, db);
	if (!NT_STATUS_IS_OK(nt_status)) {
		return nt_status;
	}

	(*db)->hdb_fetch_kvno = hdb_samba4_kpasswd_fetch_kvno;
	(*db)->hdb_firstkey = hdb_samba4_nextkey_panic;
	(*db)->hdb_nextkey = hdb_samba4_nextkey_panic;

	return NT_STATUS_OK;
}
