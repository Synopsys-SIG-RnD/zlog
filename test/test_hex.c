/*
 * This file is part of the Xlog Library.
 *
 * Copyright (C) 2011 by Hardy Simpson <HardySimpson@gmail.com>
 *
 * The Xlog Library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The Xlog Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with the Xlog Library. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#include "../xlog.h"

static int ReadTotalFile( FILE * fp , char ** ptr , long * len )
{
        long            fileLen ;
        int             nret ;
        char            * pStart ;

        *ptr = NULL;

        nret = fseek( fp , 0L , SEEK_END );
        if( nret )
        {
                return -1;
        }

        fileLen = ftell( fp );
        if( fileLen < 0 )
        {
                return -2;
        }

        if( ( pStart = calloc(1, fileLen+1) ) == NULL )
        {
                return -3;
        }

        nret = fseek( fp , 0L , SEEK_SET );
        if( nret )
        {
                free( pStart );
                return -4;
        }

        nret = fread( pStart , fileLen , 1 , fp );
        if( ferror( fp ) )
        {
                free( pStart );
                return -5;
        }

        *ptr = pStart;
        *len = fileLen;

        return 0;
}

int main(int argc, char** argv)
{
	int rc;

	FILE	*fp;
	char	*dmp;
	long	dmp_len = 0;

	if (argc != 2) {
		printf("useage: test_hex [file]\n");
		exit(1);
	}

	fp = fopen(argv[1], "r");
	if (!fp) {
		printf("fopen[%s] fail\n", argv[1]);
		exit(1);
	}
	
	xlog_category_t *my_cat;

	rc = xlog_init("test_hex.conf");
	if (rc) {
		printf("init failed\n");
		return -1;
	}
	
	my_cat = xlog_get_category("my_cat");
	if (!my_cat) {
		printf("get category failed\n");
	}


	rc = ReadTotalFile(fp, &dmp, &dmp_len);

	HXLOG_DEBUG(my_cat, dmp, dmp_len);
	fclose(fp);
	free(dmp);

	xlog_fini();
	printf("hex log end\n");
	
	return 0;
}
