/* gpg-error.h or gpgrt.h - Common code for GnuPG and others.    -*- c -*-
 * Copyright (C) 2001-2020 g10 Code GmbH
 *
 * This file is part of libgpg-error (aka libgpgrt).
 *
 * libgpg-error is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * libgpg-error is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, see <https://www.gnu.org/licenses/>.
 * SPDX-License-Identifier: LGPL-2.1+
 *
 * Do not edit.  Generated from gpg-error.h.in for:
                 x86_64-pc-darwin
 */

/* The GnuPG project consists of many components.  Error codes are
 * exchanged between all components.  The common error codes and their
 * user-presentable descriptions are kept into a shared library to
 * allow adding new error codes and components without recompiling any
 * of the other components.  In addition to error codes this library
 * also features several other groups of functions which are common to
 * all GnuPG components.  They may be used by independet project as
 * well.  The interfaces will not change in a backward incompatible way.
 *
 * An error code together with an error source build up an error
 * value.  As the error value is been passed from one component to
 * another, it preserves the information about the source and nature
 * of the error.
 *
 * A component of the GnuPG project can define the following macros to
 * tune the behaviour of the library:
 *
 * GPG_ERR_SOURCE_DEFAULT: Define to an error source of type
 * gpg_err_source_t to make that source the default for gpg_error().
 * Otherwise GPG_ERR_SOURCE_UNKNOWN is used as default.
 *
 * GPG_ERR_ENABLE_GETTEXT_MACROS: Define to provide macros to map the
 * internal gettext API to standard names.  This has only an effect on
 * Windows platforms.
 *
 * GPGRT_ENABLE_ES_MACROS: Define to provide "es_" macros for the
 * estream functions.
 *
 * GPGRT_ENABLE_LOG_MACROS: Define to provide short versions of the
 * log functions.
 *
 * GPGRT_ENABLE_ARGPARSE_MACROS: Needs to be defined to provide the
 * mandatory macros of the argparse interface.
 */

#ifndef GPG_ERROR_H
#define GPG_ERROR_H 1
#ifndef GPGRT_H
#define GPGRT_H 1

#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>

/* The version string of this header. */
#define GPG_ERROR_VERSION "1.45-unknown"
#define GPGRT_VERSION     "1.45-unknown"

/* The version number of this header. */
#define GPG_ERROR_VERSION_NUMBER 0x012d00
#define GPGRT_VERSION_NUMBER     0x012d00


#ifdef __GNUC__
# define GPG_ERR_INLINE __inline__
#elif defined(_MSC_VER) && _MSC_VER >= 1300
# define GPG_ERR_INLINE __inline
#elif defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
# define GPG_ERR_INLINE inline
#else
# ifndef GPG_ERR_INLINE
#  define GPG_ERR_INLINE
# endif
#endif

#ifdef __cplusplus
extern "C" {
#if 0 /* just to make Emacs auto-indent happy */
}
#endif
#endif /* __cplusplus */



/* The error source type gpg_err_source_t.
 *
 * Where as the Poo out of a welle small
 * Taketh his firste springing and his sours.
 *					--Chaucer.
 */

/* Only use free slots, never change or reorder the existing
 * entries.  */
typedef enum
  {
    GPG_ERR_SOURCE_UNKNOWN = 0,
    GPG_ERR_SOURCE_GCRYPT = 1,
    GPG_ERR_SOURCE_GPG = 2,
    GPG_ERR_SOURCE_GPGSM = 3,
    GPG_ERR_SOURCE_GPGAGENT = 4,
    GPG_ERR_SOURCE_PINENTRY = 5,
    GPG_ERR_SOURCE_SCD = 6,
    GPG_ERR_SOURCE_GPGME = 7,
    GPG_ERR_SOURCE_KEYBOX = 8,
    GPG_ERR_SOURCE_KSBA = 9,
    GPG_ERR_SOURCE_DIRMNGR = 10,
    GPG_ERR_SOURCE_GSTI = 11,
    GPG_ERR_SOURCE_GPA = 12,
    GPG_ERR_SOURCE_KLEO = 13,
    GPG_ERR_SOURCE_G13 = 14,
    GPG_ERR_SOURCE_ASSUAN = 15,
    GPG_ERR_SOURCE_TPM2D = 16,
    GPG_ERR_SOURCE_TLS = 17,
    GPG_ERR_SOURCE_ANY = 31,
    GPG_ERR_SOURCE_USER_1 = 32,
    GPG_ERR_SOURCE_USER_2 = 33,
    GPG_ERR_SOURCE_USER_3 = 34,
    GPG_ERR_SOURCE_USER_4 = 35,

    /* This is one more than the largest allowed entry.  */
    GPG_ERR_SOURCE_DIM = 128
  } gpg_err_source_t;


/* The error code type gpg_err_code_t.  */

/* Only use free slots, never change or reorder the existing
 * entries.  */
typedef enum
  {
    GPG_ERR_NO_ERROR = 0,
    GPG_ERR_GENERAL = 1,
    GPG_ERR_UNKNOWN_PACKET = 2,
    GPG_ERR_UNKNOWN_VERSION = 3,
    GPG_ERR_PUBKEY_ALGO = 4,
    GPG_ERR_DIGEST_ALGO = 5,
    GPG_ERR_BAD_PUBKEY = 6,
    GPG_ERR_BAD_SECKEY = 7,
    GPG_ERR_BAD_SIGNATURE = 8,
    GPG_ERR_NO_PUBKEY = 9,
    GPG_ERR_CHECKSUM = 10,
    GPG_ERR_BAD_PASSPHRASE = 11,
    GPG_ERR_CIPHER_ALGO = 12,
    GPG_ERR_KEYRING_OPEN = 13,
    GPG_ERR_INV_PACKET = 14,
    GPG_ERR_INV_ARMOR = 15,
    GPG_ERR_NO_USER_ID = 16,
    GPG_ERR_NO_SECKEY = 17,
    GPG_ERR_WRONG_SECKEY = 18,
    GPG_ERR_BAD_KEY = 19,
    GPG_ERR_COMPR_ALGO = 20,
    GPG_ERR_NO_PRIME = 21,
    GPG_ERR_NO_ENCODING_METHOD = 22,
    GPG_ERR_NO_ENCRYPTION_SCHEME = 23,
    GPG_ERR_NO_SIGNATURE_SCHEME = 24,
    GPG_ERR_INV_ATTR = 25,
    GPG_ERR_NO_VALUE = 26,
    GPG_ERR_NOT_FOUND = 27,
    GPG_ERR_VALUE_NOT_FOUND = 28,
    GPG_ERR_SYNTAX = 29,
    GPG_ERR_BAD_MPI = 30,
    GPG_ERR_INV_PASSPHRASE = 31,
    GPG_ERR_SIG_CLASS = 32,
    GPG_ERR_RESOURCE_LIMIT = 33,
    GPG_ERR_INV_KEYRING = 34,
    GPG_ERR_TRUSTDB = 35,
    GPG_ERR_BAD_CERT = 36,
    GPG_ERR_INV_USER_ID = 37,
    GPG_ERR_UNEXPECTED = 38,
    GPG_ERR_TIME_CONFLICT = 39,
    GPG_ERR_KEYSERVER = 40,
    GPG_ERR_WRONG_PUBKEY_ALGO = 41,
    GPG_ERR_TRIBUTE_TO_D_A = 42,
    GPG_ERR_WEAK_KEY = 43,
    GPG_ERR_INV_KEYLEN = 44,
    GPG_ERR_INV_ARG = 45,
    GPG_ERR_BAD_URI = 46,
    GPG_ERR_INV_URI = 47,
    GPG_ERR_NETWORK = 48,
    GPG_ERR_UNKNOWN_HOST = 49,
    GPG_ERR_SELFTEST_FAILED = 50,
    GPG_ERR_NOT_ENCRYPTED = 51,
    GPG_ERR_NOT_PROCESSED = 52,
    GPG_ERR_UNUSABLE_PUBKEY = 53,
    GPG_ERR_UNUSABLE_SECKEY = 54,
    GPG_ERR_INV_VALUE = 55,
    GPG_ERR_BAD_CERT_CHAIN = 56,
    GPG_ERR_MISSING_CERT = 57,
    GPG_ERR_NO_DATA = 58,
    GPG_ERR_BUG = 59,
    GPG_ERR_NOT_SUPPORTED = 60,
    GPG_ERR_INV_OP = 61,
    GPG_ERR_TIMEOUT = 62,
    GPG_ERR_INTERNAL = 63,
    GPG_ERR_EOF_GCRYPT = 64,
    GPG_ERR_INV_OBJ = 65,
    GPG_ERR_TOO_SHORT = 66,
    GPG_ERR_TOO_LARGE = 67,
    GPG_ERR_NO_OBJ = 68,
    GPG_ERR_NOT_IMPLEMENTED = 69,
    GPG_ERR_CONFLICT = 70,
    GPG_ERR_INV_CIPHER_MODE = 71,
    GPG_ERR_INV_FLAG = 72,
    GPG_ERR_INV_HANDLE = 73,
    GPG_ERR_TRUNCATED = 74,
    GPG_ERR_INCOMPLETE_LINE = 75,
    GPG_ERR_INV_RESPONSE = 76,
    GPG_ERR_NO_AGENT = 77,
    GPG_ERR_AGENT = 78,
    GPG_ERR_INV_DATA = 79,
    GPG_ERR_ASSUAN_SERVER_FAULT = 80,
    GPG_ERR_ASSUAN = 81,
    GPG_ERR_INV_SESSION_KEY = 82,
    GPG_ERR_INV_SEXP = 83,
    GPG_ERR_UNSUPPORTED_ALGORITHM = 84,
    GPG_ERR_NO_PIN_ENTRY = 85,
    GPG_ERR_PIN_ENTRY = 86,
    GPG_ERR_BAD_PIN = 87,
    GPG_ERR_INV_NAME = 88,
    GPG_ERR_BAD_DATA = 89,
    GPG_ERR_INV_PARAMETER = 90,
    GPG_ERR_WRONG_CARD = 91,
    GPG_ERR_NO_DIRMNGR = 92,
    GPG_ERR_DIRMNGR = 93,
    GPG_ERR_CERT_REVOKED = 94,
    GPG_ERR_NO_CRL_KNOWN = 95,
    GPG_ERR_CRL_TOO_OLD = 96,
    GPG_ERR_LINE_TOO_LONG = 97,
    GPG_ERR_NOT_TRUSTED = 98,
    GPG_ERR_CANCELED = 99,
    GPG_ERR_BAD_CA_CERT = 100,
    GPG_ERR_CERT_EXPIRED = 101,
    GPG_ERR_CERT_TOO_YOUNG = 102,
    GPG_ERR_UNSUPPORTED_CERT = 103,
    GPG_ERR_UNKNOWN_SEXP = 104,
    GPG_ERR_UNSUPPORTED_PROTECTION = 105,
    GPG_ERR_CORRUPTED_PROTECTION = 106,
    GPG_ERR_AMBIGUOUS_NAME = 107,
    GPG_ERR_CARD = 108,
    GPG_ERR_CARD_RESET = 109,
    GPG_ERR_CARD_REMOVED = 110,
    GPG_ERR_INV_CARD = 111,
    GPG_ERR_CARD_NOT_PRESENT = 112,
    GPG_ERR_NO_PKCS15_APP = 113,
    GPG_ERR_NOT_CONFIRMED = 114,
    GPG_ERR_CONFIGURATION = 115,
    GPG_ERR_NO_POLICY_MATCH = 116,
    GPG_ERR_INV_INDEX = 117,
    GPG_ERR_INV_ID = 118,
    GPG_ERR_NO_SCDAEMON = 119,
    GPG_ERR_SCDAEMON = 120,
    GPG_ERR_UNSUPPORTED_PROTOCOL = 121,
    GPG_ERR_BAD_PIN_METHOD = 122,
    GPG_ERR_CARD_NOT_INITIALIZED = 123,
    GPG_ERR_UNSUPPORTED_OPERATION = 124,
    GPG_ERR_WRONG_KEY_USAGE = 125,
    GPG_ERR_NOTHING_FOUND = 126,
    GPG_ERR_WRONG_BLOB_TYPE = 127,
    GPG_ERR_MISSING_VALUE = 128,
    GPG_ERR_HARDWARE = 129,
    GPG_ERR_PIN_BLOCKED = 130,
    GPG_ERR_USE_CONDITIONS = 131,
    GPG_ERR_PIN_NOT_SYNCED = 132,
    GPG_ERR_INV_CRL = 133,
    GPG_ERR_BAD_BER = 134,
    GPG_ERR_INV_BER = 135,
    GPG_ERR_ELEMENT_NOT_FOUND = 136,
    GPG_ERR_IDENTIFIER_NOT_FOUND = 137,
    GPG_ERR_INV_TAG = 138,
    GPG_ERR_INV_LENGTH = 139,
    GPG_ERR_INV_KEYINFO = 140,
    GPG_ERR_UNEXPECTED_TAG = 141,
    GPG_ERR_NOT_DER_ENCODED = 142,
    GPG_ERR_NO_CMS_OBJ = 143,
    GPG_ERR_INV_CMS_OBJ = 144,
    GPG_ERR_UNKNOWN_CMS_OBJ = 145,
    GPG_ERR_UNSUPPORTED_CMS_OBJ = 146,
    GPG_ERR_UNSUPPORTED_ENCODING = 147,
    GPG_ERR_UNSUPPORTED_CMS_VERSION = 148,
    GPG_ERR_UNKNOWN_ALGORITHM = 149,
    GPG_ERR_INV_ENGINE = 150,
    GPG_ERR_PUBKEY_NOT_TRUSTED = 151,
    GPG_ERR_DECRYPT_FAILED = 152,
    GPG_ERR_KEY_EXPIRED = 153,
    GPG_ERR_SIG_EXPIRED = 154,
    GPG_ERR_ENCODING_PROBLEM = 155,
    GPG_ERR_INV_STATE = 156,
    GPG_ERR_DUP_VALUE = 157,
    GPG_ERR_MISSING_ACTION = 158,
    GPG_ERR_MODULE_NOT_FOUND = 159,
    GPG_ERR_INV_OID_STRING = 160,
    GPG_ERR_INV_TIME = 161,
    GPG_ERR_INV_CRL_OBJ = 162,
    GPG_ERR_UNSUPPORTED_CRL_VERSION = 163,
    GPG_ERR_INV_CERT_OBJ = 164,
    GPG_ERR_UNKNOWN_NAME = 165,
    GPG_ERR_LOCALE_PROBLEM = 166,
    GPG_ERR_NOT_LOCKED = 167,
    GPG_ERR_PROTOCOL_VIOLATION = 168,
    GPG_ERR_INV_MAC = 169,
    GPG_ERR_INV_REQUEST = 170,
    GPG_ERR_UNKNOWN_EXTN = 171,
    GPG_ERR_UNKNOWN_CRIT_EXTN = 172,
    GPG_ERR_LOCKED = 173,
    GPG_ERR_UNKNOWN_OPTION = 174,
    GPG_ERR_UNKNOWN_COMMAND = 175,
    GPG_ERR_NOT_OPERATIONAL = 176,
    GPG_ERR_NO_PASSPHRASE = 177,
    GPG_ERR_NO_PIN = 178,
    GPG_ERR_NOT_ENABLED = 179,
    GPG_ERR_NO_ENGINE = 180,
    GPG_ERR_MISSING_KEY = 181,
    GPG_ERR_TOO_MANY = 182,
    GPG_ERR_LIMIT_REACHED = 183,
    GPG_ERR_NOT_INITIALIZED = 184,
    GPG_ERR_MISSING_ISSUER_CERT = 185,
    GPG_ERR_NO_KEYSERVER = 186,
    GPG_ERR_INV_CURVE = 187,
    GPG_ERR_UNKNOWN_CURVE = 188,
    GPG_ERR_DUP_KEY = 189,
    GPG_ERR_AMBIGUOUS = 190,
    GPG_ERR_NO_CRYPT_CTX = 191,
    GPG_ERR_WRONG_CRYPT_CTX = 192,
    GPG_ERR_BAD_CRYPT_CTX = 193,
    GPG_ERR_CRYPT_CTX_CONFLICT = 194,
    GPG_ERR_BROKEN_PUBKEY = 195,
    GPG_ERR_BROKEN_SECKEY = 196,
    GPG_ERR_MAC_ALGO = 197,
    GPG_ERR_FULLY_CANCELED = 198,
    GPG_ERR_UNFINISHED = 199,
    GPG_ERR_BUFFER_TOO_SHORT = 200,
    GPG_ERR_SEXP_INV_LEN_SPEC = 201,
    GPG_ERR_SEXP_STRING_TOO_LONG = 202,
    GPG_ERR_SEXP_UNMATCHED_PAREN = 203,
    GPG_ERR_SEXP_NOT_CANONICAL = 204,
    GPG_ERR_SEXP_BAD_CHARACTER = 205,
    GPG_ERR_SEXP_BAD_QUOTATION = 206,
    GPG_ERR_SEXP_ZERO_PREFIX = 207,
    GPG_ERR_SEXP_NESTED_DH = 208,
    GPG_ERR_SEXP_UNMATCHED_DH = 209,
    GPG_ERR_SEXP_UNEXPECTED_PUNC = 210,
    GPG_ERR_SEXP_BAD_HEX_CHAR = 211,
    GPG_ERR_SEXP_ODD_HEX_NUMBERS = 212,
    GPG_ERR_SEXP_BAD_OCT_CHAR = 213,
    GPG_ERR_SUBKEYS_EXP_OR_REV = 217,
    GPG_ERR_DB_CORRUPTED = 218,
    GPG_ERR_SERVER_FAILED = 219,
    GPG_ERR_NO_NAME = 220,
    GPG_ERR_NO_KEY = 221,
    GPG_ERR_LEGACY_KEY = 222,
    GPG_ERR_REQUEST_TOO_SHORT = 223,
    GPG_ERR_REQUEST_TOO_LONG = 224,
    GPG_ERR_OBJ_TERM_STATE = 225,
    GPG_ERR_NO_CERT_CHAIN = 226,
    GPG_ERR_CERT_TOO_LARGE = 227,
    GPG_ERR_INV_RECORD = 228,
    GPG_ERR_BAD_MAC = 229,
    GPG_ERR_UNEXPECTED_MSG = 230,
    GPG_ERR_COMPR_FAILED = 231,
    GPG_ERR_WOULD_WRAP = 232,
    GPG_ERR_FATAL_ALERT = 233,
    GPG_ERR_NO_CIPHER = 234,
    GPG_ERR_MISSING_CLIENT_CERT = 235,
    GPG_ERR_CLOSE_NOTIFY = 236,
    GPG_ERR_TICKET_EXPIRED = 237,
    GPG_ERR_BAD_TICKET = 238,
    GPG_ERR_UNKNOWN_IDENTITY = 239,
    GPG_ERR_BAD_HS_CERT = 240,
    GPG_ERR_BAD_HS_CERT_REQ = 241,
    GPG_ERR_BAD_HS_CERT_VER = 242,
    GPG_ERR_BAD_HS_CHANGE_CIPHER = 243,
    GPG_ERR_BAD_HS_CLIENT_HELLO = 244,
    GPG_ERR_BAD_HS_SERVER_HELLO = 245,
    GPG_ERR_BAD_HS_SERVER_HELLO_DONE = 246,
    GPG_ERR_BAD_HS_FINISHED = 247,
    GPG_ERR_BAD_HS_SERVER_KEX = 248,
    GPG_ERR_BAD_HS_CLIENT_KEX = 249,
    GPG_ERR_BOGUS_STRING = 250,
    GPG_ERR_FORBIDDEN = 251,
    GPG_ERR_KEY_DISABLED = 252,
    GPG_ERR_KEY_ON_CARD = 253,
    GPG_ERR_INV_LOCK_OBJ = 254,
    GPG_ERR_TRUE = 255,
    GPG_ERR_FALSE = 256,
    GPG_ERR_ASS_GENERAL = 257,
    GPG_ERR_ASS_ACCEPT_FAILED = 258,
    GPG_ERR_ASS_CONNECT_FAILED = 259,
    GPG_ERR_ASS_INV_RESPONSE = 260,
    GPG_ERR_ASS_INV_VALUE = 261,
    GPG_ERR_ASS_INCOMPLETE_LINE = 262,
    GPG_ERR_ASS_LINE_TOO_LONG = 263,
    GPG_ERR_ASS_NESTED_COMMANDS = 264,
    GPG_ERR_ASS_NO_DATA_CB = 265,
    GPG_ERR_ASS_NO_INQUIRE_CB = 266,
    GPG_ERR_ASS_NOT_A_SERVER = 267,
    GPG_ERR_ASS_NOT_A_CLIENT = 268,
    GPG_ERR_ASS_SERVER_START = 269,
    GPG_ERR_ASS_READ_ERROR = 270,
    GPG_ERR_ASS_WRITE_ERROR = 271,
    GPG_ERR_ASS_TOO_MUCH_DATA = 273,
    GPG_ERR_ASS_UNEXPECTED_CMD = 274,
    GPG_ERR_ASS_UNKNOWN_CMD = 275,
    GPG_ERR_ASS_SYNTAX = 276,
    GPG_ERR_ASS_CANCELED = 277,
    GPG_ERR_ASS_NO_INPUT = 278,
    GPG_ERR_ASS_NO_OUTPUT = 279,
    GPG_ERR_ASS_PARAMETER = 280,
    GPG_ERR_ASS_UNKNOWN_INQUIRE = 281,
    GPG_ERR_ENGINE_TOO_OLD = 300,
    GPG_ERR_WINDOW_TOO_SMALL = 301,
    GPG_ERR_WINDOW_TOO_LARGE = 302,
    GPG_ERR_MISSING_ENVVAR = 303,
    GPG_ERR_USER_ID_EXISTS = 304,
    GPG_ERR_NAME_EXISTS = 305,
    GPG_ERR_DUP_NAME = 306,
    GPG_ERR_TOO_YOUNG = 307,
    GPG_ERR_TOO_OLD = 308,
    GPG_ERR_UNKNOWN_FLAG = 309,
    GPG_ERR_INV_ORDER = 310,
    GPG_ERR_ALREADY_FETCHED = 311,
    GPG_ERR_TRY_LATER = 312,
    GPG_ERR_WRONG_NAME = 313,
    GPG_ERR_NO_AUTH = 314,
    GPG_ERR_BAD_AUTH = 315,
    GPG_ERR_NO_KEYBOXD = 316,
    GPG_ERR_KEYBOXD = 317,
    GPG_ERR_NO_SERVICE = 318,
    GPG_ERR_SERVICE = 319,
    GPG_ERR_SYSTEM_BUG = 666,
    GPG_ERR_DNS_UNKNOWN = 711,
    GPG_ERR_DNS_SECTION = 712,
    GPG_ERR_DNS_ADDRESS = 713,
    GPG_ERR_DNS_NO_QUERY = 714,
    GPG_ERR_DNS_NO_ANSWER = 715,
    GPG_ERR_DNS_CLOSED = 716,
    GPG_ERR_DNS_VERIFY = 717,
    GPG_ERR_DNS_TIMEOUT = 718,
    GPG_ERR_LDAP_GENERAL = 721,
    GPG_ERR_LDAP_ATTR_GENERAL = 722,
    GPG_ERR_LDAP_NAME_GENERAL = 723,
    GPG_ERR_LDAP_SECURITY_GENERAL = 724,
    GPG_ERR_LDAP_SERVICE_GENERAL = 725,
    GPG_ERR_LDAP_UPDATE_GENERAL = 726,
    GPG_ERR_LDAP_E_GENERAL = 727,
    GPG_ERR_LDAP_X_GENERAL = 728,
    GPG_ERR_LDAP_OTHER_GENERAL = 729,
    GPG_ERR_LDAP_X_CONNECTING = 750,
    GPG_ERR_LDAP_REFERRAL_LIMIT = 751,
    GPG_ERR_LDAP_CLIENT_LOOP = 752,
    GPG_ERR_LDAP_NO_RESULTS = 754,
    GPG_ERR_LDAP_CONTROL_NOT_FOUND = 755,
    GPG_ERR_LDAP_NOT_SUPPORTED = 756,
    GPG_ERR_LDAP_CONNECT = 757,
    GPG_ERR_LDAP_NO_MEMORY = 758,
    GPG_ERR_LDAP_PARAM = 759,
    GPG_ERR_LDAP_USER_CANCELLED = 760,
    GPG_ERR_LDAP_FILTER = 761,
    GPG_ERR_LDAP_AUTH_UNKNOWN = 762,
    GPG_ERR_LDAP_TIMEOUT = 763,
    GPG_ERR_LDAP_DECODING = 764,
    GPG_ERR_LDAP_ENCODING = 765,
    GPG_ERR_LDAP_LOCAL = 766,
    GPG_ERR_LDAP_SERVER_DOWN = 767,
    GPG_ERR_LDAP_SUCCESS = 768,
    GPG_ERR_LDAP_OPERATIONS = 769,
    GPG_ERR_LDAP_PROTOCOL = 770,
    GPG_ERR_LDAP_TIMELIMIT = 771,
    GPG_ERR_LDAP_SIZELIMIT = 772,
    GPG_ERR_LDAP_COMPARE_FALSE = 773,
    GPG_ERR_LDAP_COMPARE_TRUE = 774,
    GPG_ERR_LDAP_UNSUPPORTED_AUTH = 775,
    GPG_ERR_LDAP_STRONG_AUTH_RQRD = 776,
    GPG_ERR_LDAP_PARTIAL_RESULTS = 777,
    GPG_ERR_LDAP_REFERRAL = 778,
    GPG_ERR_LDAP_ADMINLIMIT = 779,
    GPG_ERR_LDAP_UNAVAIL_CRIT_EXTN = 780,
    GPG_ERR_LDAP_CONFIDENT_RQRD = 781,
    GPG_ERR_LDAP_SASL_BIND_INPROG = 782,
    GPG_ERR_LDAP_NO_SUCH_ATTRIBUTE = 784,
    GPG_ERR_LDAP_UNDEFINED_TYPE = 785,
    GPG_ERR_LDAP_BAD_MATCHING = 786,
    GPG_ERR_LDAP_CONST_VIOLATION = 787,
    GPG_ERR_LDAP_TYPE_VALUE_EXISTS = 788,
    GPG_ERR_LDAP_INV_SYNTAX = 789,
    GPG_ERR_LDAP_NO_SUCH_OBJ = 800,
    GPG_ERR_LDAP_ALIAS_PROBLEM = 801,
    GPG_ERR_LDAP_INV_DN_SYNTAX = 802,
    GPG_ERR_LDAP_IS_LEAF = 803,
    GPG_ERR_LDAP_ALIAS_DEREF = 804,
    GPG_ERR_LDAP_X_PROXY_AUTH_FAIL = 815,
    GPG_ERR_LDAP_BAD_AUTH = 816,
    GPG_ERR_LDAP_INV_CREDENTIALS = 817,
    GPG_ERR_LDAP_INSUFFICIENT_ACC = 818,
    GPG_ERR_LDAP_BUSY = 819,
    GPG_ERR_LDAP_UNAVAILABLE = 820,
    GPG_ERR_LDAP_UNWILL_TO_PERFORM = 821,
    GPG_ERR_LDAP_LOOP_DETECT = 822,
    GPG_ERR_LDAP_NAMING_VIOLATION = 832,
    GPG_ERR_LDAP_OBJ_CLS_VIOLATION = 833,
    GPG_ERR_LDAP_NOT_ALLOW_NONLEAF = 834,
    GPG_ERR_LDAP_NOT_ALLOW_ON_RDN = 835,
    GPG_ERR_LDAP_ALREADY_EXISTS = 836,
    GPG_ERR_LDAP_NO_OBJ_CLASS_MODS = 837,
    GPG_ERR_LDAP_RESULTS_TOO_LARGE = 838,
    GPG_ERR_LDAP_AFFECTS_MULT_DSAS = 839,
    GPG_ERR_LDAP_VLV = 844,
    GPG_ERR_LDAP_OTHER = 848,
    GPG_ERR_LDAP_CUP_RESOURCE_LIMIT = 881,
    GPG_ERR_LDAP_CUP_SEC_VIOLATION = 882,
    GPG_ERR_LDAP_CUP_INV_DATA = 883,
    GPG_ERR_LDAP_CUP_UNSUP_SCHEME = 884,
    GPG_ERR_LDAP_CUP_RELOAD = 885,
    GPG_ERR_LDAP_CANCELLED = 886,
    GPG_ERR_LDAP_NO_SUCH_OPERATION = 887,
    GPG_ERR_LDAP_TOO_LATE = 888,
    GPG_ERR_LDAP_CANNOT_CANCEL = 889,
    GPG_ERR_LDAP_ASSERTION_FAILED = 890,
    GPG_ERR_LDAP_PROX_AUTH_DENIED = 891,
    GPG_ERR_USER_1 = 1024,
    GPG_ERR_USER_2 = 1025,
    GPG_ERR_USER_3 = 1026,
    GPG_ERR_USER_4 = 1027,
    GPG_ERR_USER_5 = 1028,
    GPG_ERR_USER_6 = 1029,
    GPG_ERR_USER_7 = 1030,
    GPG_ERR_USER_8 = 1031,
    GPG_ERR_USER_9 = 1032,
    GPG_ERR_USER_10 = 1033,
    GPG_ERR_USER_11 = 1034,
    GPG_ERR_USER_12 = 1035,
    GPG_ERR_USER_13 = 1036,
    GPG_ERR_USER_14 = 1037,
    GPG_ERR_USER_15 = 1038,
    GPG_ERR_USER_16 = 1039,
    GPG_ERR_SQL_OK = 1500,
    GPG_ERR_SQL_ERROR = 1501,
    GPG_ERR_SQL_INTERNAL = 1502,
    GPG_ERR_SQL_PERM = 1503,
    GPG_ERR_SQL_ABORT = 1504,
    GPG_ERR_SQL_BUSY = 1505,
    GPG_ERR_SQL_LOCKED = 1506,
    GPG_ERR_SQL_NOMEM = 1507,
    GPG_ERR_SQL_READONLY = 1508,
    GPG_ERR_SQL_INTERRUPT = 1509,
    GPG_ERR_SQL_IOERR = 1510,
    GPG_ERR_SQL_CORRUPT = 1511,
    GPG_ERR_SQL_NOTFOUND = 1512,
    GPG_ERR_SQL_FULL = 1513,
    GPG_ERR_SQL_CANTOPEN = 1514,
    GPG_ERR_SQL_PROTOCOL = 1515,
    GPG_ERR_SQL_EMPTY = 1516,
    GPG_ERR_SQL_SCHEMA = 1517,
    GPG_ERR_SQL_TOOBIG = 1518,
    GPG_ERR_SQL_CONSTRAINT = 1519,
    GPG_ERR_SQL_MISMATCH = 1520,
    GPG_ERR_SQL_MISUSE = 1521,
    GPG_ERR_SQL_NOLFS = 1522,
    GPG_ERR_SQL_AUTH = 1523,
    GPG_ERR_SQL_FORMAT = 1524,
    GPG_ERR_SQL_RANGE = 1525,
    GPG_ERR_SQL_NOTADB = 1526,
    GPG_ERR_SQL_NOTICE = 1527,
    GPG_ERR_SQL_WARNING = 1528,
    GPG_ERR_SQL_ROW = 1600,
    GPG_ERR_SQL_DONE = 1601,
    GPG_ERR_MISSING_ERRNO = 16381,
    GPG_ERR_UNKNOWN_ERRNO = 16382,
    GPG_ERR_EOF = 16383,

    /* The following error codes are used to map system errors.  */
#define GPG_ERR_SYSTEM_ERROR	(1 << 15)
    GPG_ERR_E2BIG = GPG_ERR_SYSTEM_ERROR | 0,
    GPG_ERR_EACCES = GPG_ERR_SYSTEM_ERROR | 1,
    GPG_ERR_EADDRINUSE = GPG_ERR_SYSTEM_ERROR | 2,
    GPG_ERR_EADDRNOTAVAIL = GPG_ERR_SYSTEM_ERROR | 3,
    GPG_ERR_EADV = GPG_ERR_SYSTEM_ERROR | 4,
    GPG_ERR_EAFNOSUPPORT = GPG_ERR_SYSTEM_ERROR | 5,
    GPG_ERR_EAGAIN = GPG_ERR_SYSTEM_ERROR | 6,
    GPG_ERR_EALREADY = GPG_ERR_SYSTEM_ERROR | 7,
    GPG_ERR_EAUTH = GPG_ERR_SYSTEM_ERROR | 8,
    GPG_ERR_EBACKGROUND = GPG_ERR_SYSTEM_ERROR | 9,
    GPG_ERR_EBADE = GPG_ERR_SYSTEM_ERROR | 10,
    GPG_ERR_EBADF = GPG_ERR_SYSTEM_ERROR | 11,
    GPG_ERR_EBADFD = GPG_ERR_SYSTEM_ERROR | 12,
    GPG_ERR_EBADMSG = GPG_ERR_SYSTEM_ERROR | 13,
    GPG_ERR_EBADR = GPG_ERR_SYSTEM_ERROR | 14,
    GPG_ERR_EBADRPC = GPG_ERR_SYSTEM_ERROR | 15,
    GPG_ERR_EBADRQC = GPG_ERR_SYSTEM_ERROR | 16,
    GPG_ERR_EBADSLT = GPG_ERR_SYSTEM_ERROR | 17,
    GPG_ERR_EBFONT = GPG_ERR_SYSTEM_ERROR | 18,
    GPG_ERR_EBUSY = GPG_ERR_SYSTEM_ERROR | 19,
    GPG_ERR_ECANCELED = GPG_ERR_SYSTEM_ERROR | 20,
    GPG_ERR_ECHILD = GPG_ERR_SYSTEM_ERROR | 21,
    GPG_ERR_ECHRNG = GPG_ERR_SYSTEM_ERROR | 22,
    GPG_ERR_ECOMM = GPG_ERR_SYSTEM_ERROR | 23,
    GPG_ERR_ECONNABORTED = GPG_ERR_SYSTEM_ERROR | 24,
    GPG_ERR_ECONNREFUSED = GPG_ERR_SYSTEM_ERROR | 25,
    GPG_ERR_ECONNRESET = GPG_ERR_SYSTEM_ERROR | 26,
    GPG_ERR_ED = GPG_ERR_SYSTEM_ERROR | 27,
    GPG_ERR_EDEADLK = GPG_ERR_SYSTEM_ERROR | 28,
    GPG_ERR_EDEADLOCK = GPG_ERR_SYSTEM_ERROR | 29,
    GPG_ERR_EDESTADDRREQ = GPG_ERR_SYSTEM_ERROR | 30,
    GPG_ERR_EDIED = GPG_ERR_SYSTEM_ERROR | 31,
    GPG_ERR_EDOM = GPG_ERR_SYSTEM_ERROR | 32,
    GPG_ERR_EDOTDOT = GPG_ERR_SYSTEM_ERROR | 33,
    GPG_ERR_EDQUOT = GPG_ERR_SYSTEM_ERROR | 34,
    GPG_ERR_EEXIST = GPG_ERR_SYSTEM_ERROR | 35,
    GPG_ERR_EFAULT = GPG_ERR_SYSTEM_ERROR | 36,
    GPG_ERR_EFBIG = GPG_ERR_SYSTEM_ERROR | 37,
    GPG_ERR_EFTYPE = GPG_ERR_SYSTEM_ERROR | 38,
    GPG_ERR_EGRATUITOUS = GPG_ERR_SYSTEM_ERROR | 39,
    GPG_ERR_EGREGIOUS = GPG_ERR_SYSTEM_ERROR | 40,
    GPG_ERR_EHOSTDOWN = GPG_ERR_SYSTEM_ERROR | 41,
    GPG_ERR_EHOSTUNREACH = GPG_ERR_SYSTEM_ERROR | 42,
    GPG_ERR_EIDRM = GPG_ERR_SYSTEM_ERROR | 43,
    GPG_ERR_EIEIO = GPG_ERR_SYSTEM_ERROR | 44,
    GPG_ERR_EILSEQ = GPG_ERR_SYSTEM_ERROR | 45,
    GPG_ERR_EINPROGRESS = GPG_ERR_SYSTEM_ERROR | 46,
    GPG_ERR_EINTR = GPG_ERR_SYSTEM_ERROR | 47,
    GPG_ERR_EINVAL = GPG_ERR_SYSTEM_ERROR | 48,
    GPG_ERR_EIO = GPG_ERR_SYSTEM_ERROR | 49,
    GPG_ERR_EISCONN = GPG_ERR_SYSTEM_ERROR | 50,
    GPG_ERR_EISDIR = GPG_ERR_SYSTEM_ERROR | 51,
    GPG_ERR_EISNAM = GPG_ERR_SYSTEM_ERROR | 52,
    GPG_ERR_EL2HLT = GPG_ERR_SYSTEM_ERROR | 53,
    GPG_ERR_EL2NSYNC = GPG_ERR_SYSTEM_ERROR | 54,
    GPG_ERR_EL3HLT = GPG_ERR_SYSTEM_ERROR | 55,
    GPG_ERR_EL3RST = GPG_ERR_SYSTEM_ERROR | 56,
    GPG_ERR_ELIBACC = GPG_ERR_SYSTEM_ERROR | 57,
    GPG_ERR_ELIBBAD = GPG_ERR_SYSTEM_ERROR | 58,
    GPG_ERR_ELIBEXEC = GPG_ERR_SYSTEM_ERROR | 59,
    GPG_ERR_ELIBMAX = GPG_ERR_SYSTEM_ERROR | 60,
    GPG_ERR_ELIBSCN = GPG_ERR_SYSTEM_ERROR | 61,
    GPG_ERR_ELNRNG = GPG_ERR_SYSTEM_ERROR | 62,
    GPG_ERR_ELOOP = GPG_ERR_SYSTEM_ERROR | 63,
    GPG_ERR_EMEDIUMTYPE = GPG_ERR_SYSTEM_ERROR | 64,
    GPG_ERR_EMFILE = GPG_ERR_SYSTEM_ERROR | 65,
    GPG_ERR_EMLINK = GPG_ERR_SYSTEM_ERROR | 66,
    GPG_ERR_EMSGSIZE = GPG_ERR_SYSTEM_ERROR | 67,
    GPG_ERR_EMULTIHOP = GPG_ERR_SYSTEM_ERROR | 68,
    GPG_ERR_ENAMETOOLONG = GPG_ERR_SYSTEM_ERROR | 69,
    GPG_ERR_ENAVAIL = GPG_ERR_SYSTEM_ERROR | 70,
    GPG_ERR_ENEEDAUTH = GPG_ERR_SYSTEM_ERROR | 71,
    GPG_ERR_ENETDOWN = GPG_ERR_SYSTEM_ERROR | 72,
    GPG_ERR_ENETRESET = GPG_ERR_SYSTEM_ERROR | 73,
    GPG_ERR_ENETUNREACH = GPG_ERR_SYSTEM_ERROR | 74,
    GPG_ERR_ENFILE = GPG_ERR_SYSTEM_ERROR | 75,
    GPG_ERR_ENOANO = GPG_ERR_SYSTEM_ERROR | 76,
    GPG_ERR_ENOBUFS = GPG_ERR_SYSTEM_ERROR | 77,
    GPG_ERR_ENOCSI = GPG_ERR_SYSTEM_ERROR | 78,
    GPG_ERR_ENODATA = GPG_ERR_SYSTEM_ERROR | 79,
    GPG_ERR_ENODEV = GPG_ERR_SYSTEM_ERROR | 80,
    GPG_ERR_ENOENT = GPG_ERR_SYSTEM_ERROR | 81,
    GPG_ERR_ENOEXEC = GPG_ERR_SYSTEM_ERROR | 82,
    GPG_ERR_ENOLCK = GPG_ERR_SYSTEM_ERROR | 83,
    GPG_ERR_ENOLINK = GPG_ERR_SYSTEM_ERROR | 84,
    GPG_ERR_ENOMEDIUM = GPG_ERR_SYSTEM_ERROR | 85,
    GPG_ERR_ENOMEM = GPG_ERR_SYSTEM_ERROR | 86,
    GPG_ERR_ENOMSG = GPG_ERR_SYSTEM_ERROR | 87,
    GPG_ERR_ENONET = GPG_ERR_SYSTEM_ERROR | 88,
    GPG_ERR_ENOPKG = GPG_ERR_SYSTEM_ERROR | 89,
    GPG_ERR_ENOPROTOOPT = GPG_ERR_SYSTEM_ERROR | 90,
    GPG_ERR_ENOSPC = GPG_ERR_SYSTEM_ERROR | 91,
    GPG_ERR_ENOSR = GPG_ERR_SYSTEM_ERROR | 92,
    GPG_ERR_ENOSTR = GPG_ERR_SYSTEM_ERROR | 93,
    GPG_ERR_ENOSYS = GPG_ERR_SYSTEM_ERROR | 94,
    GPG_ERR_ENOTBLK = GPG_ERR_SYSTEM_ERROR | 95,
    GPG_ERR_ENOTCONN = GPG_ERR_SYSTEM_ERROR | 96,
    GPG_ERR_ENOTDIR = GPG_ERR_SYSTEM_ERROR | 97,
    GPG_ERR_ENOTEMPTY = GPG_ERR_SYSTEM_ERROR | 98,
    GPG_ERR_ENOTNAM = GPG_ERR_SYSTEM_ERROR | 99,
    GPG_ERR_ENOTSOCK = GPG_ERR_SYSTEM_ERROR | 100,
    GPG_ERR_ENOTSUP = GPG_ERR_SYSTEM_ERROR | 101,
    GPG_ERR_ENOTTY = GPG_ERR_SYSTEM_ERROR | 102,
    GPG_ERR_ENOTUNIQ = GPG_ERR_SYSTEM_ERROR | 103,
    GPG_ERR_ENXIO = GPG_ERR_SYSTEM_ERROR | 104,
    GPG_ERR_EOPNOTSUPP = GPG_ERR_SYSTEM_ERROR | 105,
    GPG_ERR_EOVERFLOW = GPG_ERR_SYSTEM_ERROR | 106,
    GPG_ERR_EPERM = GPG_ERR_SYSTEM_ERROR | 107,
    GPG_ERR_EPFNOSUPPORT = GPG_ERR_SYSTEM_ERROR | 108,
    GPG_ERR_EPIPE = GPG_ERR_SYSTEM_ERROR | 109,
    GPG_ERR_EPROCLIM = GPG_ERR_SYSTEM_ERROR | 110,
    GPG_ERR_EPROCUNAVAIL = GPG_ERR_SYSTEM_ERROR | 111,
    GPG_ERR_EPROGMISMATCH = GPG_ERR_SYSTEM_ERROR | 112,
    GPG_ERR_EPROGUNAVAIL = GPG_ERR_SYSTEM_ERROR | 113,
    GPG_ERR_EPROTO = GPG_ERR_SYSTEM_ERROR | 114,
    GPG_ERR_EPROTONOSUPPORT = GPG_ERR_SYSTEM_ERROR | 115,
    GPG_ERR_EPROTOTYPE = GPG_ERR_SYSTEM_ERROR | 116,
    GPG_ERR_ERANGE = GPG_ERR_SYSTEM_ERROR | 117,
    GPG_ERR_EREMCHG = GPG_ERR_SYSTEM_ERROR | 118,
    GPG_ERR_EREMOTE = GPG_ERR_SYSTEM_ERROR | 119,
    GPG_ERR_EREMOTEIO = GPG_ERR_SYSTEM_ERROR | 120,
    GPG_ERR_ERESTART = GPG_ERR_SYSTEM_ERROR | 121,
    GPG_ERR_EROFS = GPG_ERR_SYSTEM_ERROR | 122,
    GPG_ERR_ERPCMISMATCH = GPG_ERR_SYSTEM_ERROR | 123,
    GPG_ERR_ESHUTDOWN = GPG_ERR_SYSTEM_ERROR | 124,
    GPG_ERR_ESOCKTNOSUPPORT = GPG_ERR_SYSTEM_ERROR | 125,
    GPG_ERR_ESPIPE = GPG_ERR_SYSTEM_ERROR | 126,
    GPG_ERR_ESRCH = GPG_ERR_SYSTEM_ERROR | 127,
    GPG_ERR_ESRMNT = GPG_ERR_SYSTEM_ERROR | 128,
    GPG_ERR_ESTALE = GPG_ERR_SYSTEM_ERROR | 129,
    GPG_ERR_ESTRPIPE = GPG_ERR_SYSTEM_ERROR | 130,
    GPG_ERR_ETIME = GPG_ERR_SYSTEM_ERROR | 131,
    GPG_ERR_ETIMEDOUT = GPG_ERR_SYSTEM_ERROR | 132,
    GPG_ERR_ETOOMANYREFS = GPG_ERR_SYSTEM_ERROR | 133,
    GPG_ERR_ETXTBSY = GPG_ERR_SYSTEM_ERROR | 134,
    GPG_ERR_EUCLEAN = GPG_ERR_SYSTEM_ERROR | 135,
    GPG_ERR_EUNATCH = GPG_ERR_SYSTEM_ERROR | 136,
    GPG_ERR_EUSERS = GPG_ERR_SYSTEM_ERROR | 137,
    GPG_ERR_EWOULDBLOCK = GPG_ERR_SYSTEM_ERROR | 138,
    GPG_ERR_EXDEV = GPG_ERR_SYSTEM_ERROR | 139,
    GPG_ERR_EXFULL = GPG_ERR_SYSTEM_ERROR | 140,

    /* This is one more than the largest allowed entry.  */
    GPG_ERR_CODE_DIM = 65536
  } gpg_err_code_t;


/* The error value type gpg_error_t.  */

/* We would really like to use bit-fields in a struct, but using
 * structs as return values can cause binary compatibility issues, in
 * particular if you want to do it efficiently (also see
 * -freg-struct-return option to GCC).  */
typedef unsigned int gpg_error_t;

/* We use the lowest 16 bits of gpg_error_t for error codes.  The 16th
 * bit indicates system errors.  */
#define GPG_ERR_CODE_MASK	(GPG_ERR_CODE_DIM - 1)

/* Bits 17 to 24 are reserved.  */

/* We use the upper 7 bits of gpg_error_t for error sources.  */
#define GPG_ERR_SOURCE_MASK	(GPG_ERR_SOURCE_DIM - 1)
#define GPG_ERR_SOURCE_SHIFT	24

/* The highest bit is reserved.  It shouldn't be used to prevent
 * potential negative numbers when transmitting error values as
 * text.  */


/*
 * GCC feature test.
 */
#if __GNUC__
# define _GPG_ERR_GCC_VERSION (__GNUC__ * 10000 \
                               + __GNUC_MINOR__ * 100 \
                               + __GNUC_PATCHLEVEL__)
#else
# define _GPG_ERR_GCC_VERSION 0
#endif

#undef _GPG_ERR_HAVE_CONSTRUCTOR
#if _GPG_ERR_GCC_VERSION > 30100
# define _GPG_ERR_CONSTRUCTOR	__attribute__ ((__constructor__))
# define _GPG_ERR_HAVE_CONSTRUCTOR
#else
# define _GPG_ERR_CONSTRUCTOR
#endif

#define GPGRT_GCC_VERSION  _GPG_ERR_GCC_VERSION

#if _GPG_ERR_GCC_VERSION >= 29200
# define _GPGRT__RESTRICT __restrict__
#else
# define _GPGRT__RESTRICT
#endif

/* The noreturn attribute.  */
#if _GPG_ERR_GCC_VERSION >= 20500
# define GPGRT_ATTR_NORETURN   __attribute__ ((__noreturn__))
#else
# define GPGRT_ATTR_NORETURN
#endif

/* The printf attributes.  */
#if _GPG_ERR_GCC_VERSION >= 40400
# define GPGRT_ATTR_PRINTF(f, a) \
                    __attribute__ ((format(__gnu_printf__,f,a)))
# define GPGRT_ATTR_NR_PRINTF(f, a) \
                    __attribute__ ((__noreturn__, format(__gnu_printf__,f,a)))
#elif _GPG_ERR_GCC_VERSION >= 20500
# define GPGRT_ATTR_PRINTF(f, a) \
                    __attribute__ ((format(printf,f,a)))
# define GPGRT_ATTR_NR_PRINTF(f, a) \
                    __attribute__ ((__noreturn__, format(printf,f,a)))
#else
# define GPGRT_ATTR_PRINTF(f, a)
# define GPGRT_ATTR_NR_PRINTF(f, a)
#endif
#if _GPG_ERR_GCC_VERSION >= 20800
# define GPGRT_ATTR_FORMAT_ARG(a)  __attribute__ ((__format_arg__ (a)))
#else
# define GPGRT_ATTR_FORMAT_ARG(a)
#endif

/* The sentinel attribute.  */
#if _GPG_ERR_GCC_VERSION >= 40000
# define GPGRT_ATTR_SENTINEL(a)  __attribute__ ((sentinel(a)))
#else
# define GPGRT_ATTR_SENTINEL(a)
#endif

/* The used and unused attributes.
 * I am not sure since when the unused attribute is really supported.
 * In any case it it only needed for gcc versions which print a
 * warning.  Thus let us require gcc >= 3.5.  */
#if _GPG_ERR_GCC_VERSION >= 40000
# define GPGRT_ATTR_USED  __attribute__ ((used))
#else
# define GPGRT_ATTR_USED
#endif
#if _GPG_ERR_GCC_VERSION >= 30500
# define GPGRT_ATTR_UNUSED  __attribute__ ((unused))
#else
# define GPGRT_ATTR_UNUSED
#endif

/* The deprecated attribute.  */
#if _GPG_ERR_GCC_VERSION >= 30100
# define GPGRT_ATTR_DEPRECATED  __attribute__ ((__deprecated__))
#else
# define GPGRT_ATTR_DEPRECATED
#endif

/* The pure attribute.  */
#if _GPG_ERR_GCC_VERSION >= 29600
# define GPGRT_ATTR_PURE  __attribute__ ((__pure__))
#else
# define GPGRT_ATTR_PURE
#endif

/* The malloc attribute.  */
#if _GPG_ERR_GCC_VERSION >= 30200
# define GPGRT_ATTR_MALLOC  __attribute__ ((__malloc__))
#else
# define GPGRT_ATTR_MALLOC
#endif

/* A macro defined if a GCC style __FUNCTION__ macro is available.  */
#undef GPGRT_HAVE_MACRO_FUNCTION
#if _GPG_ERR_GCC_VERSION >= 20500
# define GPGRT_HAVE_MACRO_FUNCTION 1
#endif

/* A macro defined if the pragma GCC push_options is available.  */
#undef GPGRT_HAVE_PRAGMA_GCC_PUSH
#if _GPG_ERR_GCC_VERSION >= 40400
# define GPGRT_HAVE_PRAGMA_GCC_PUSH 1
#endif

/* Detect LeakSanitizer (LSan) support for GCC and Clang based on
 * whether AddressSanitizer (ASAN) is enabled via -fsanitize=address).
 * Note that -fsanitize=leak just affect the linker options which
 * cannot be detected here.  In that case you have to define the
 * GPGRT_HAVE_LEAK_SANITIZER macro manually.  */
#ifdef __GNUC__
# ifdef __SANITIZE_ADDRESS__
#  define GPGRT_HAVE_LEAK_SANITIZER
# elif defined(__has_feature)
#  if __has_feature(address_sanitizer)
#   define GPGRT_HAVE_LEAK_SANITIZER
#  endif
# endif
#endif


/* The new name for the inline macro.  */
#define GPGRT_INLINE GPG_ERR_INLINE

#ifdef GPGRT_HAVE_LEAK_SANITIZER
# include <sanitizer/lsan_interface.h>
#endif

/* Mark heap objects as non-leaked memory. */
static GPGRT_INLINE void
gpgrt_annotate_leaked_object (const void *p)
{
#ifdef GPGRT_HAVE_LEAK_SANITIZER
  __lsan_ignore_object(p);
#else
  (void)p;
#endif
}


/*
 * Initialization function.
 */

/* Initialize the library.  This function should be run early.  */
gpg_error_t gpg_err_init (void) _GPG_ERR_CONSTRUCTOR;

/* If this is defined, the library is already initialized by the
   constructor and does not need to be initialized explicitely.  */
#undef GPG_ERR_INITIALIZED
#ifdef _GPG_ERR_HAVE_CONSTRUCTOR
# define GPG_ERR_INITIALIZED	1
# define gpgrt_init() do { gpg_err_init (); } while (0)
#else
# define gpgrt_init() do { ; } while (0)
#endif

/* See the source on how to use the deinit function; it is usually not
   required.  */
void gpg_err_deinit (int mode);

/* Register blocking system I/O clamping functions.  */
void gpgrt_set_syscall_clamp (void (*pre)(void), void (*post)(void));

/* Get current I/O clamping functions.  */
void gpgrt_get_syscall_clamp (void (**r_pre)(void), void (**r_post)(void));

/* Register a custom malloc/realloc/free function.  */
void gpgrt_set_alloc_func  (void *(*f)(void *a, size_t n));

/* Register an emergency cleanup handler.  */
void gpgrt_add_emergency_cleanup (void (*f)(void));

/* Wrapper around abort to make sure emergency cleanups are run.  */
void gpgrt_abort (void) GPGRT_ATTR_NORETURN;



/*
 * Constructor and accessor functions.
 */

/* Construct an error value from an error code and source.  Within a
 * subsystem, use gpg_error.  */
static GPG_ERR_INLINE gpg_error_t
gpg_err_make (gpg_err_source_t source, gpg_err_code_t code)
{
  return code == GPG_ERR_NO_ERROR ? GPG_ERR_NO_ERROR
    : (((source & GPG_ERR_SOURCE_MASK) << GPG_ERR_SOURCE_SHIFT)
       | (code & GPG_ERR_CODE_MASK));
}


/* The user should define GPG_ERR_SOURCE_DEFAULT before including this
 * file to specify a default source for gpg_error.  */
#ifndef GPG_ERR_SOURCE_DEFAULT
#define GPG_ERR_SOURCE_DEFAULT	GPG_ERR_SOURCE_UNKNOWN
#endif

static GPG_ERR_INLINE gpg_error_t
gpg_error (gpg_err_code_t code)
{
  return gpg_err_make (GPG_ERR_SOURCE_DEFAULT, code);
}


/* Retrieve the error code from an error value.  */
static GPG_ERR_INLINE gpg_err_code_t
gpg_err_code (gpg_error_t err)
{
  return (gpg_err_code_t) (err & GPG_ERR_CODE_MASK);
}


/* Retrieve the error source from an error value.  */
static GPG_ERR_INLINE gpg_err_source_t
gpg_err_source (gpg_error_t err)
{
  return (gpg_err_source_t) ((err >> GPG_ERR_SOURCE_SHIFT)
			     & GPG_ERR_SOURCE_MASK);
}


/* String functions.  */

/* Return a pointer to a string containing a description of the error
 * code in the error value ERR.  This function is not thread-safe.  */
const char *gpg_strerror (gpg_error_t err);

/* Return the error string for ERR in the user-supplied buffer BUF of
 * size BUFLEN.  This function is, in contrast to gpg_strerror,
 * thread-safe if a thread-safe strerror_r() function is provided by
 * the system.  If the function succeeds, 0 is returned and BUF
 * contains the string describing the error.  If the buffer was not
 * large enough, ERANGE is returned and BUF contains as much of the
 * beginning of the error string as fits into the buffer.  */
int gpg_strerror_r (gpg_error_t err, char *buf, size_t buflen);

/* Return a pointer to a string containing a description of the error
 * source in the error value ERR.  */
const char *gpg_strsource (gpg_error_t err);


/*
 * Mapping of system errors (errno).
 */

/* Retrieve the error code for the system error ERR.  This returns
 * GPG_ERR_UNKNOWN_ERRNO if the system error is not mapped (report
 * this). */
gpg_err_code_t gpg_err_code_from_errno (int err);

/* Retrieve the system error for the error code CODE.  This returns 0
 * if CODE is not a system error code.  */
int gpg_err_code_to_errno (gpg_err_code_t code);

/* Retrieve the error code directly from the ERRNO variable.  This
 * returns GPG_ERR_UNKNOWN_ERRNO if the system error is not mapped
 * (report this) and GPG_ERR_MISSING_ERRNO if ERRNO has the value 0. */
gpg_err_code_t gpg_err_code_from_syserror (void);

/* Mapper for SQLite primary error codes.  */
static GPG_ERR_INLINE gpg_error_t
gpg_err_code_from_sqlite (int sqlres)
{
  return sqlres? GPG_ERR_SQL_OK + (sqlres & 0xff) : 0;
}


/* Set the ERRNO variable.  This function is the preferred way to set
 * ERRNO due to peculiarities on WindowsCE.  */
void gpg_err_set_errno (int err);

/* Return or check the version.  Both functions are identical.  */
const char *gpgrt_check_version (const char *req_version);
const char *gpg_error_check_version (const char *req_version);

/* System specific type definitions.  */
#include <sys/types.h>

typedef ssize_t gpgrt_ssize_t;

typedef long gpgrt_off_t;




/* Self-documenting convenience functions.  */

static GPG_ERR_INLINE gpg_error_t
gpg_err_make_from_errno (gpg_err_source_t source, int err)
{
  return gpg_err_make (source, gpg_err_code_from_errno (err));
}


static GPG_ERR_INLINE gpg_error_t
gpg_error_from_errno (int err)
{
  return gpg_error (gpg_err_code_from_errno (err));
}

static GPG_ERR_INLINE gpg_error_t
gpg_error_from_syserror (void)
{
  return gpg_error (gpg_err_code_from_syserror ());
}



/*
 * Malloc and friends
 */

void *gpgrt_realloc (void *a, size_t n);
void *gpgrt_reallocarray (void *a, size_t oldnmemb, size_t nmemb, size_t size);
void *gpgrt_malloc (size_t n);
void *gpgrt_calloc (size_t n, size_t m);
char *gpgrt_strdup (const char *string);
char *gpgrt_strconcat (const char *s1, ...) GPGRT_ATTR_SENTINEL(0);
void gpgrt_free (void *a);


/*
 * System specific function wrappers.
 */

/* A getenv replacement which mallocs the returned string.  */
char *gpgrt_getenv (const char *name);

/* A setenv and a unsetenv replacement.*/
gpg_err_code_t gpgrt_setenv (const char *name,
                             const char *value, int overwrite);
#define gpgrt_unsetenv(n) gpgrt_setenv ((n), NULL, 1)

/* A wrapper around mkdir using a string for the mode.  */
gpg_err_code_t gpgrt_mkdir (const char *name, const char *modestr);

/* A simple wrapper around chdir.  */
gpg_err_code_t gpgrt_chdir (const char *name);

/* Return the current WD as a malloced string.  */
char *gpgrt_getcwd (void);

/* A wrapper around access to handle UTF-8 on Windows.  */
gpg_err_code_t gpgrt_access (const char *fname, int mode);




/*
 * Lock functions.
 */

