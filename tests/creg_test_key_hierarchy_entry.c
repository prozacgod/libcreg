/*
 * Library key_hierarchy_entry type test program
 *
 * Copyright (C) 2013-2026, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <file_stream.h>
#include <memory.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "creg_test_libcerror.h"
#include "creg_test_libcreg.h"
#include "creg_test_macros.h"
#include "creg_test_memory.h"
#include "creg_test_unused.h"

#include "../libcreg/libcreg_key_hierarchy_entry.h"

/* Key hierarchy entries of a SYSTEM.DAT created by the Windows 98 SE
 * REGEDIT.EXE from:
 *
 * REGEDIT4
 *
 * [HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion]
 * "Minimal"="1"
 *
 * creg_test_key_hierarchy_entry_data1 is the root key at offset 0x20 and
 * creg_test_key_hierarchy_entry_data2 the Software key at offset 0x3c
 */
uint8_t creg_test_key_hierarchy_entry_data1[ 28 ] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
	0x3c, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

uint8_t creg_test_key_hierarchy_entry_data2[ 28 ] = {
	0x00, 0x00, 0x00, 0x00, 0x6b, 0x02, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x20, 0x00, 0x00, 0x00,
	0x58, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00 };

#if defined( __GNUC__ ) && !defined( LIBCREG_DLL_IMPORT )

/* Tests the libcreg_key_hierarchy_entry_initialize function
 * Returns 1 if successful or 0 if not
 */
int creg_test_key_hierarchy_entry_initialize(
     void )
{
	libcerror_error_t *error                           = NULL;
	libcreg_key_hierarchy_entry_t *key_hierarchy_entry = NULL;
	int result                                         = 0;

#if defined( HAVE_CREG_TEST_MEMORY )
	int number_of_malloc_fail_tests                    = 1;
	int number_of_memset_fail_tests                    = 1;
	int test_number                                    = 0;
#endif

	/* Test regular cases
	 */
	result = libcreg_key_hierarchy_entry_initialize(
	          &key_hierarchy_entry,
	          &error );

	CREG_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CREG_TEST_ASSERT_IS_NOT_NULL(
	 "key_hierarchy_entry",
	 key_hierarchy_entry );

	CREG_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcreg_key_hierarchy_entry_free(
	          &key_hierarchy_entry,
	          &error );

	CREG_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CREG_TEST_ASSERT_IS_NULL(
	 "key_hierarchy_entry",
	 key_hierarchy_entry );

	CREG_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libcreg_key_hierarchy_entry_initialize(
	          NULL,
	          &error );

	CREG_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CREG_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	key_hierarchy_entry = (libcreg_key_hierarchy_entry_t *) 0x12345678UL;

	result = libcreg_key_hierarchy_entry_initialize(
	          &key_hierarchy_entry,
	          &error );

	key_hierarchy_entry = NULL;

	CREG_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CREG_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_CREG_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libcreg_key_hierarchy_entry_initialize with malloc failing
		 */
		creg_test_malloc_attempts_before_fail = test_number;

		result = libcreg_key_hierarchy_entry_initialize(
		          &key_hierarchy_entry,
		          &error );

		if( creg_test_malloc_attempts_before_fail != -1 )
		{
			creg_test_malloc_attempts_before_fail = -1;

			if( key_hierarchy_entry != NULL )
			{
				libcreg_key_hierarchy_entry_free(
				 &key_hierarchy_entry,
				 NULL );
			}
		}
		else
		{
			CREG_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			CREG_TEST_ASSERT_IS_NULL(
			 "key_hierarchy_entry",
			 key_hierarchy_entry );

			CREG_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libcreg_key_hierarchy_entry_initialize with memset failing
		 */
		creg_test_memset_attempts_before_fail = test_number;

		result = libcreg_key_hierarchy_entry_initialize(
		          &key_hierarchy_entry,
		          &error );

		if( creg_test_memset_attempts_before_fail != -1 )
		{
			creg_test_memset_attempts_before_fail = -1;

			if( key_hierarchy_entry != NULL )
			{
				libcreg_key_hierarchy_entry_free(
				 &key_hierarchy_entry,
				 NULL );
			}
		}
		else
		{
			CREG_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			CREG_TEST_ASSERT_IS_NULL(
			 "key_hierarchy_entry",
			 key_hierarchy_entry );

			CREG_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_CREG_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( key_hierarchy_entry != NULL )
	{
		libcreg_key_hierarchy_entry_free(
		 &key_hierarchy_entry,
		 NULL );
	}
	return( 0 );
}

/* Tests the libcreg_key_hierarchy_entry_free function
 * Returns 1 if successful or 0 if not
 */
int creg_test_key_hierarchy_entry_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libcreg_key_hierarchy_entry_free(
	          NULL,
	          &error );

	CREG_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CREG_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libcreg_key_hierarchy_entry_read_data function
 * Returns 1 if successful or 0 if not
 */
int creg_test_key_hierarchy_entry_read_data(
     void )
{
	libcerror_error_t *error                           = NULL;
	libcreg_key_hierarchy_entry_t *key_hierarchy_entry = NULL;
	int result                                         = 0;

	/* Initialize test
	 */
	result = libcreg_key_hierarchy_entry_initialize(
	          &key_hierarchy_entry,
	          &error );

	CREG_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CREG_TEST_ASSERT_IS_NOT_NULL(
	 "key_hierarchy_entry",
	 key_hierarchy_entry );

	CREG_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libcreg_key_hierarchy_entry_read_data(
	          NULL,
	          NULL,
	          0,
	          0,
	          &error );

	CREG_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CREG_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libcreg_key_hierarchy_entry_read_data(
	          key_hierarchy_entry,
	          NULL,
	          0,
	          0,
	          &error );

	CREG_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CREG_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libcreg_key_hierarchy_entry_free(
	          &key_hierarchy_entry,
	          &error );

	CREG_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CREG_TEST_ASSERT_IS_NULL(
	 "key_hierarchy_entry",
	 key_hierarchy_entry );

	CREG_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( key_hierarchy_entry != NULL )
	{
		libcreg_key_hierarchy_entry_free(
		 &key_hierarchy_entry,
		 NULL );
	}
	return( 0 );
}

/* Tests the libcreg_key_hierarchy_entry_write_data function
 * Returns 1 if successful or 0 if not
 */
int creg_test_key_hierarchy_entry_write_data(
     void )
{
	uint8_t data[ 28 ];

	libcerror_error_t *error                                = NULL;
	libcreg_key_hierarchy_entry_t *key_hierarchy_entry      = NULL;
	libcreg_key_hierarchy_entry_t *read_key_hierarchy_entry = NULL;
	int result                                              = 0;

	/* Initialize test
	 */
	result = libcreg_key_hierarchy_entry_initialize(
	          &key_hierarchy_entry,
	          &error );

	CREG_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CREG_TEST_ASSERT_IS_NOT_NULL(
	 "key_hierarchy_entry",
	 key_hierarchy_entry );

	CREG_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcreg_key_hierarchy_entry_initialize(
	          &read_key_hierarchy_entry,
	          &error );

	CREG_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CREG_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 *
	 * The next free key hierarchy entry offset (bytes 8 - 11) is not compared,
	 * in an entry that is in use REGEDIT.EXE leaves it as it was in the free
	 * entry the key hierarchy entry was allocated from.
	 */
	key_hierarchy_entry->name_hash             = 0;
	key_hierarchy_entry->parent_key_offset     = 0xffffffffUL;
	key_hierarchy_entry->sub_key_offset        = 0x0000003cUL;
	key_hierarchy_entry->next_key_offset       = 0xffffffffUL;
	key_hierarchy_entry->key_name_entry_number = 0xffff;
	key_hierarchy_entry->data_block_number     = 0xffff;

	memory_set(
	 data,
	 0xaa,
	 28 );

	result = libcreg_key_hierarchy_entry_write_data(
	          key_hierarchy_entry,
	          data,
	          28,
	          &error );

	CREG_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CREG_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          data,
	          creg_test_key_hierarchy_entry_data1,
	          8 );

	CREG_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	result = memory_compare(
	          &( data[ 12 ] ),
	          &( creg_test_key_hierarchy_entry_data1[ 12 ] ),
	          16 );

	CREG_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	key_hierarchy_entry->name_hash             = 0x0000026bUL;
	key_hierarchy_entry->parent_key_offset     = 0x00000020UL;
	key_hierarchy_entry->sub_key_offset        = 0x00000058UL;
	key_hierarchy_entry->next_key_offset       = 0xffffffffUL;
	key_hierarchy_entry->key_name_entry_number = 0;
	key_hierarchy_entry->data_block_number     = 0;

	memory_set(
	 data,
	 0xaa,
	 28 );

	result = libcreg_key_hierarchy_entry_write_data(
	          key_hierarchy_entry,
	          data,
	          28,
	          &error );

	CREG_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CREG_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          data,
	          creg_test_key_hierarchy_entry_data2,
	          8 );

	CREG_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	result = memory_compare(
	          &( data[ 12 ] ),
	          &( creg_test_key_hierarchy_entry_data2[ 12 ] ),
	          16 );

	CREG_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Read back the written key hierarchy entry
	 */
	result = libcreg_key_hierarchy_entry_read_data(
	          read_key_hierarchy_entry,
	          data,
	          28,
	          0x3c,
	          &error );

	CREG_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CREG_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	CREG_TEST_ASSERT_EQUAL_UINT32(
	 "read_key_hierarchy_entry->name_hash",
	 read_key_hierarchy_entry->name_hash,
	 (uint32_t) 0x0000026bUL );

	CREG_TEST_ASSERT_EQUAL_UINT32(
	 "read_key_hierarchy_entry->parent_key_offset",
	 read_key_hierarchy_entry->parent_key_offset,
	 (uint32_t) 0x00000020UL );

	CREG_TEST_ASSERT_EQUAL_UINT32(
	 "read_key_hierarchy_entry->sub_key_offset",
	 read_key_hierarchy_entry->sub_key_offset,
	 (uint32_t) 0x00000058UL );

	CREG_TEST_ASSERT_EQUAL_UINT32(
	 "read_key_hierarchy_entry->next_key_offset",
	 read_key_hierarchy_entry->next_key_offset,
	 (uint32_t) 0xffffffffUL );

	/* Test error cases
	 */
	result = libcreg_key_hierarchy_entry_write_data(
	          NULL,
	          data,
	          28,
	          &error );

	CREG_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CREG_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libcreg_key_hierarchy_entry_write_data(
	          key_hierarchy_entry,
	          NULL,
	          28,
	          &error );

	CREG_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CREG_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libcreg_key_hierarchy_entry_write_data(
	          key_hierarchy_entry,
	          data,
	          27,
	          &error );

	CREG_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CREG_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libcreg_key_hierarchy_entry_free(
	          &read_key_hierarchy_entry,
	          &error );

	CREG_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CREG_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcreg_key_hierarchy_entry_free(
	          &key_hierarchy_entry,
	          &error );

	CREG_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CREG_TEST_ASSERT_IS_NULL(
	 "key_hierarchy_entry",
	 key_hierarchy_entry );

	CREG_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( read_key_hierarchy_entry != NULL )
	{
		libcreg_key_hierarchy_entry_free(
		 &read_key_hierarchy_entry,
		 NULL );
	}
	if( key_hierarchy_entry != NULL )
	{
		libcreg_key_hierarchy_entry_free(
		 &key_hierarchy_entry,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBCREG_DLL_IMPORT ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc CREG_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] CREG_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc CREG_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] CREG_TEST_ATTRIBUTE_UNUSED )
#endif
{
	CREG_TEST_UNREFERENCED_PARAMETER( argc )
	CREG_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBCREG_DLL_IMPORT )

	CREG_TEST_RUN(
	 "libcreg_key_hierarchy_entry_initialize",
	 creg_test_key_hierarchy_entry_initialize );

	CREG_TEST_RUN(
	 "libcreg_key_hierarchy_entry_free",
	 creg_test_key_hierarchy_entry_free );

	CREG_TEST_RUN(
	 "libcreg_key_hierarchy_entry_read_data",
	 creg_test_key_hierarchy_entry_read_data );

	CREG_TEST_RUN(
	 "libcreg_key_hierarchy_entry_write_data",
	 creg_test_key_hierarchy_entry_write_data );

#endif /* defined( __GNUC__ ) && !defined( LIBCREG_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBCREG_DLL_IMPORT )

on_error:
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBCREG_DLL_IMPORT ) */
}

