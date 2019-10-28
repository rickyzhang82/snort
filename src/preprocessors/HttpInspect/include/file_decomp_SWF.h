/* $Id$ */
/*
** file_decomp_SWF.h
**
** Copyright (C) 2014-2019 Cisco and/or its affiliates. All rights reserved.
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License Version 2 as
** published by the Free Software Foundation.  You may not use, modify or
** distribute this program under any other version of the GNU General
** Public License.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef FILE_DECOMP_SWF_H
#define FILE_DECOMP_SWF_H

#include <zlib.h>
#ifdef LZMA
#include <lzma.h>
#endif

/* Both ZLIB & LZMA files have an uncompressed eight byte header.  The signature is
   three bytes.  The header consists of a three byte sig, a one byte version,
   and a four byte uncompressed length (little-endian).  */

#define SWF_SIG_LEN       (3)
#define SWF_VER_LEN       (1)
#define SWF_UCL_LEN       (4)

/* LZMA Files have an additional nine bytes of header prior to the compressed data.
   This includes a four byte compressed length (little-endian) and five bytes
   of LZMA properties. */
#define SWF_LZMA_CML_LEN  (4)
#define SWF_LZMA_PRP_LEN  (5)

/* AFTER the sig, the max number of header bytes to fetch.
   VER+UCL+CML+LZMA_PRP -> 14 bytes. */
#define SWF_MAX_HEADER    (14)

/* Types */

typedef enum swf_states
{
    SWF_STATE_NEW = 0,
    SWF_STATE_GET_HEADER = 1, /* Found sig bytes, looking for end of uncomp header */
    SWF_STATE_PROC_HEADER,    /* Found header bytes, now process the header */
    SWF_STATE_DATA            /* Done with header, looking for start of data */
} fd_SWF_States;

typedef struct fd_SWF_s
{
    z_stream StreamZLIB;
#ifdef LZMA
    lzma_stream StreamLZMA;
#endif
    uint8_t Header_Bytes[SWF_MAX_HEADER];
    uint8_t State;
    uint8_t Header_Len;
    uint8_t Header_Cnt;
} fd_SWF_t;

/* API Functions */

fd_status_t File_Decomp_Init_SWF( fd_session_p_t SessionPtr );

fd_status_t File_Decomp_SWF( fd_session_p_t SessionPtr );

fd_status_t File_Decomp_End_SWF( fd_session_p_t SessionPtr );

#endif /* FILE_DECOMP_SWF_H */
