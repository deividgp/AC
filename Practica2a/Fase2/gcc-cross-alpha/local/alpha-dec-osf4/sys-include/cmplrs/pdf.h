/*
 * *****************************************************************
 * *                                                               *
 * *    Copyright (c) Digital Equipment Corporation, 1991, 1999    *
 * *                                                               *
 * *   All Rights Reserved.  Unpublished rights  reserved  under   *
 * *   the copyright laws of the United States.                    *
 * *                                                               *
 * *   The software contained on this media  is  proprietary  to   *
 * *   and  embodies  the  confidential  technology  of  Digital   *
 * *   Equipment Corporation.  Possession, use,  duplication  or   *
 * *   dissemination of the software and media is authorized only  *
 * *   pursuant to a valid written license from Digital Equipment  *
 * *   Corporation.                                                *
 * *                                                               *
 * *   RESTRICTED RIGHTS LEGEND   Use, duplication, or disclosure  *
 * *   by the U.S. Government is subject to restrictions  as  set  *
 * *   forth in Subparagraph (c)(1)(ii)  of  DFARS  252.227-7013,  *
 * *   or  in  FAR 52.227-19, as applicable.                       *
 * *                                                               *
 * *****************************************************************
 */
/*
 * HISTORY
 */
/*
 * @(#)$RCSfile: pdf.h,v $ $Revision: 1.1.9.2 $ (DEC) $Date: 1998/02/18 21:55:03 $
 */

#ifndef _CMPLRS_PDF_H_
#define _CMPLRS_PDF_H_
#ifdef __cplusplus        
extern "C" {               
#endif                      

#include <stdarg.h>
#include <sys/types.h>

/* data types supported for fields of records in a PDF file */
typedef enum pdf_type {
         PDF_STRING,   		/*   null-terminated string */
         PDF_UNSIGNED_CHAR,	/*   unsigned char : 1 bytes */
         PDF_UNSIGNED_SHORT,	/*   unsigned short : 2 bytes */
         PDF_UNSIGNED_INT,	/*   unsigned int : 4 bytes */
         PDF_UNSIGNED_LONG,	/*   unsigned long : 8 bytes */
         PDF_SIGNED_CHAR,	/*   signed char : 1 bytes */
         PDF_SIGNED_SHORT,	/*   signed short : 2 bytes */
         PDF_SIGNED_INT,	/*   signed int : 4 bytes */
         PDF_SIGNED_LONG,	/*   signed long : 8 bytes */
         PDF_CHAR,		/*   character : 1 byte */
         PDF_WCHAR2,		/*   wide character : 2 byte */
         PDF_WCHAR4,		/*   wide character : 4 byte */
         PDF_WCHAR8,		/*   wide character : 8 byte */
         PDF_FLOAT,		/*   float : 4 bytes */
         PDF_DOUBLE		/*   double : 8 bytes */
} pdf_type_t;

/* definitions of various aspects of a type of record */
typedef long pdf_def_t;		/* one of the following kinds of definition */
#define PDF_RECORD	-1	/* the first and only the first definition;
				 * names the record type being described */
#define PDF_ATTR	-2	/* specifies an attribute of the last preceding
				 * definition in the description, ie the record
				 * as a whole or one of its fields; must not be
				 * PDF_FLOAT or PDF_DOUBLE type */
#define PDF_SCALAR	-3	/* defines a single-valued field of the record; 
				 * can be any pdf_type_t except PDF_STRING */
#define PDF_VSIZE	-4	/* defines a field of the record whose value
				 * is the number of elements in the PDF_VARRAY
				 * definition that follows it; must be a
				 * PDF_UNSIGNED_* type */
#define PDF_VARRAY	-5	/* defines a variable length array field having
				 * the number of elements specified by either:
				 *  - the number of characters (including the
				 *    terminating null) in its string value,
				 *    if its pdf_type_t is PDF_STRING
				 *  - the value of the preceding PDF_VSIZE
				 *    field, for all other pdf_type_t */
#define PDF_ARRAY(dimension) ((unsigned int)dimension)
				/* defines a fixed length array field having
				 * 'dimension' elements; can be a PDF_STRING
				 * (is zero-filled after the terminating null)
				 * or have elements of any other pdf_type */

/* An array of pdf_record_t (terminated by one with NULL 'name') describes a
 * PDF record, its fields, and their application-specific attributes, if any: 
 *	- the name 
 *	- the data type of the value of each field or attribute
 *	- the value of each attribute
 * Attribute-value fields of type double or float are not currently supported.
 */
typedef struct pdf_record {
	pdf_def_t  definition_type;	
	char	   *name;
	pdf_type_t data_type;	/* only for field / attribute definition_type */
	void	   *value;	/* only for attribute definition_type */
} pdf_record_t;

/* pdf_[read|write]_header flags.
 *
 * The alignment flags are only used by producers of pdf files.
 * PDF_NOALIGN might be selected for output to a pipe, to reduce the amount
 * of data transferred by the producer and consumer.
 * PDF_ALIGN provides natural alignment for the fields of a record,
 * so a disk file can be memory-mapped and accessed without either causing
 * unaligned-access warnings or having to compile with special switches
 * to generate code that handles unaligned data (but tends to be slower).
 * Group similarly sized fields together for best packing density when aligned.
 *
 * The MAP flags control whether an input/output file is memory mapped.
 * PDF_NOMAP should be selected for input/output to a pipe.
 * PDF_MAP causes the input or output file to be memory mapped.
 * The default values are PDF_ALIGN and PDF_MAP.
 *
 * The PDF_READ_WRITE flag allows a PDF_ARRAY or PDF_VARRAY field read from
 * an input file to be modified in place and for PDF_SCALAR fields read from
 * an input file to be modified using pdf_update_field(), so long as the
 * file was opened for read and write. The PDF_SHARED flag must also be
 * specified if such updates to input files are to be written back to the disk.
 */
typedef enum pdf_flag {
        PDF_ALIGN	= 1,	/* Natural alignment of data */
        PDF_NOALIGN	= 2,	/* No alignment of output fields */
        PDF_MAP         = 4,	/* Memory map the input/output file */
        PDF_NOMAP       = 8,	/* No memory mapping of the file */
	PDF_READ_WRITE	= 16,	/* Memory-map an input file for read & write */
	PDF_SHARED	= 32	/* Write PDF_READ_WRITE updates to disk file */
} pdf_flag_t;

/* PDF file handle.  Used in all read or write operations on a PDF file */
typedef struct pdf_file pdf_file_t;

/* PDF record marker.  Used to remember the location of a record 
 * to be read again later.
 */
typedef long pdf_mark_t;

/* PDF completion status codes, returned by all PDF procedures
 * (PDF_SUCCESS = 0 = normal completion).
 */

/*
 * Error handling.
 *
 * Each PDF routine returns one of the following condition codes.
 *
 * Any signal received during a PDF routine, and any error detected by it, is 
 * fatal to the processing of the PDF file being operated on, because PDF 
 * routines depend on the successful completion of a series of operations, and 
 * they implement no transaction rollback when interrupted or when an error is
 * detected. Typically, the application will abandon this PDF file. To
 * recover, and retry the processing, the PDF file must be pdf_close'd
 * and processing restarted from the beginning.
 */
typedef enum pdf_status {
    
    /* Version 1 */

    PDF_SUCCESS,	/* Successful completion of operation */
    PDF_AGAIN,		/* No data currently available, but not EOF */
    PDF_ARRAY_FIELD,	/* The named field is not an array */
    PDF_ATTRIBUTE_NAME,	/* No such attribute is defined by the file */
    PDF_ATTR_UNKNOWN,	/* No value is defined by PDF for this attribute name */
    PDF_CURRENT_RECORD,	/* No record has been read from the file */
    PDF_DEFINITION,	/* Invalid kind of record definition item */
    PDF_EOF,		/* End of file reached */
    PDF_EMPTY_NAME,	/* Name of field must be at least one character */
    PDF_EXTEND,		/* Unable to extend output file */
    PDF_FIELD_NAME,	/* No such field is defined for this record */
    PDF_FIELD_READ,	/* Field not read from file */
    PDF_FIXED_STRING,	/* String value longer than fixed-length field */
    PDF_HEADER,		/* Attributes & descs must precede records */
    PDF_INCOMPLETE,	/* Premature EOF caused incomplete record */
    PDF_INPUT_FILE,	/* Non-NULL input PDF-file required for reading */
    PDF_MAGIC,		/* Invalid magic number in file */
    PDF_MMAP,		/* Unable to map file */
    PDF_MEMORY,		/* Unable to allocate memory */
    PDF_NULL_POINTER,	/* Name or string-value of field or attribute is NULL */
    PDF_ONE_VSIZE,	/* One VSIZE must precede non-STRING VARRAY */
    PDF_OUTPUT_FILE,	/* Non-NULL output PDF-file required for writing */
    PDF_READ,		/* Unable to read from file */
    PDF_RECORD_COUNT,	/* Too many records defined, or none, 1-2^32 allowed */
    PDF_RECORD_DUP,	/* Only one PDF_RECORD allowed per description*/
    PDF_RECORD_NAME,	/* No such record is defined */
    PDF_SCALAR_STRING,	/* Scalars can not be strings; only (v)arrays can */
    PDF_STAT,		/* Unable to find length of file */
    PDF_STRLEN,		/* Invalid string length read from file */
    PDF_TAG,		/* Record tag out of range */
    PDF_TRUNCATE,	/* Unable to truncate completed output file */
    PDF_TYPE,		/* Invalid data type */
    PDF_UNMAP,		/* Unable to unmap file */
    PDF_VALUE_UNAVAIL,	/* Unable to get value for PDF-defined attribute */
    PDF_VERSION,	/* Invalid PDF version in file */
    PDF_VSIZE_FIXED,	/* No VSIZE allowed before fixed-length field */
    PDF_VSIZE_STRING,	/* No VSIZE allowed before PDF_STRING */
    PDF_VSIZE_TYPE,	/* VSIZE fields must be an unsigned type */
    PDF_WRITE,		/* Unable to write to file */
    
    /* Version 2 */

    PDF_MARKER,		/* Record marker invalid or larger than mapped file */
    PDF_SEEK,		/* Unable to mark or seek a record, eg in a pipe */
    PDF_UPDATE		/* Only scalars can be updated by pdf_update_field */
} pdf_status_t;

/* 
 * Producer routines for writing a pdf file.  Calls must be executed in
 * this order:
 *
 * pdf_write_header
 * pdf_write_file_attr or pdf_write_named_file_attr	
 * pdf_write_record_desc
 * pdf_write_fields
 * pdf_close
 */

/*
 * pdf_write_header
 *
 * Writes a PDF file header to the file with the given file descriptor.
 * Maps the file into memory if the descriptor references a regular file, 
 * unless PDF_NOMAP is set in the flags argument.
 * If the flags argument is zero, the default value (PDF_ALIGN|PDF_MAP) is used.
 * The returned pointer to private memory identifies the file for later
 * PDF library calls to write record definitions, attributes, and data records
 * to the file.
 *
 * Returns 0 if successful.
 * Sets errno and returns a descriptive error-code on error. 
 */
extern pdf_status_t pdf_write_header(int fd, 
				     int flags, 
				     pdf_file_t **file);

/*
 * pdf_write_file_attr
 *
 * Specifies a name/value pair to be stored in the file to record
 * some attribute of the file. The attribute name is a string, and
 * the value is the address of an appropriate value (ie. the address
 * of an integer, of a floating point number, or of the first character
 * of a string) for the given data type of the attribute.
 *
 * Returns 0 if successful, or sets errno and returns 
 * a descriptive error-code on error.
 */
extern pdf_status_t pdf_write_file_attr(pdf_file_t *file,
			       		const char *attr_name,
			       		pdf_type_t attr_type,
			       		void *attr_value);

/*
 * pdf_write_named_file_attr
 *
 * Specifies one of the pre-defined file attributes.
 * These attributes' names have the reserved "pdf_" prefix, and their values 
 * are automatically generated to describe the running system, by means of
 * the following system-calls, so no value need be provided:
 *    -	"pdf_clock_rate"		getsysinfo(GSI_CLK_TCK,...)
 *		PDF_UNSIGNED_LONG
 *    -	"pdf_cycle_rate"		getsysinfo(GSI_GET_HWRPB,...)
 *		PDF_UNSIGNED_LONG		[rpb_counter in struct rpb]
 *    -	"pdf_processor_type"		getsysinfo(GSI_PROC_TYPE,...) 
 *		PDF_UNSIGNED_LONG		[low 32 bits]
 *    -	"pdf_node_name"			uname(...) 
 *		PDF_STRING			[nodename in struct utsname]
 *    -	"pdf_os_version"		uname(...) 
 *		PDF_STRING			[release in struct utsname]
 *
 * Returns 0 if successful, or sets errno and returns
 * a descriptive error-code on error.
 */
extern pdf_status_t pdf_write_named_file_attr(pdf_file_t *file, 
					      const char *attr_name);

/*
 * pdf_write_record_desc
 *
 * Describes the name, fields, and attributes of a record that
 * may be written to the file. Each call describes one type of record.
 * The elements of the desc array describes the record, fields and
 * optional attributes.  At least one record descriptor must be provided
 * for the file.
 * Returns 0 if successful, or sets errno and returns 
 * a descriptive error-code on error.
 */
extern pdf_status_t pdf_write_record_desc(pdf_file_t *file, 
					  const pdf_record_t *desc);

/*	
 * pdf_write_fields
 * 
 * Writes the fields of the named record type to the file, where that record
 * was described in a previous call to pdf_write_record_desc().
 *
 * The unnamed arguments are the address of the first byte of the value
 * for each field of the record, in the order they were described in the 
 * pdf_record_t array passed to pdf_write_record_desc().
 * 
 * The data actually written to a file is determined by the description 
 * of the named record type and by the PDF library. The library adds
 * padding as needed, if data alignment was requested, and it adds
 * a tag field to distinguish the record type, if more than one record
 * type was specified for this file.
 * 
 * Returns 0 if successful.
 * Sets errno and returns a descriptive error-code on error. 
 */
extern pdf_status_t pdf_write_fields(pdf_file_t *file, 
				     const char *record_name, 
				     ...);

/*
 * Consumer routines for reading a pdf file.  The routines support
 * consumers that process entire records, or consumers that process
 * only selected records or selected fields of records.
 */

/*
 * pdf_read_header
 *
 * Reads and verifies a PDF file header and all attributes and record
 * descriptions from the file referenced by the given file descriptor.
 *
 * Maps the file into memory if the descriptor references a regular file, 
 * unless the flags argument contains PDF_NOMAP.
 * PDF_READ_WRITE allows the memory to be updated. If PDF_SHARED is also
 * specified, the modifications to the memory are also written to the file.
 * If flags is zero, the default value (PDF_MAP) is used.
 *
 * The PDF_ALIGN and PDF_NOALIGN flags are ignored, since 
 * the file's alignment is set by the producer of the file.
 *
 * The returned pointer to private memory identifies the file for later
 * PDF library calls to access definitions and attributes, and to read
 * data records from the file. 
 *
 * Returns 0 if successful.
 * Sets errno and returns a descriptive error-code on error. 
 */
extern pdf_status_t pdf_read_header(int fd, 
				    int flags, 
				    pdf_file_t **file);

/*
 * pdf_read_record
 *
 * Reads a record from the file. If the record name string  
 * is NULL, the next record in the file is read; otherwise the next 
 * record of the named type is read, and all intervening records with
 * different type names are skipped. The record is read into private
 * buffers. The fields of the record can be individually accessed by 
 * calling pdf_field() or pdf_fields() with the same file pointer.
 * Fields should be extracted before the next call to pdf_read_record() 
 * because it may overwrite the buffers. 
 *
 * Returns 0 if a record was read, returns PDF_EOF if the file contains no 
 * more records, returns PDF_AGAIN if the input record (eg a pipe) currently
 * has no more data (but is not at end-of file, and may gain more data later), 
 * or sets errno and returns a descriptive error-code on error. 
 */
extern pdf_status_t pdf_read_record(pdf_file_t *file,
				    const char *record_name);

/*
 * pdf_mark_record
 *
 * Provides a marker for the record that was last read from the file.
 * The marker can be passed to pdf_seek_record() later, to reset the file
 * to this same record for re-processing.
 *
 * The file must be an input file, but it can be memory-mapped or not.
 *
 * Returns 0 if successful, or sets errno and returns
 * a descriptive error-code on error.
 */
extern pdf_status_t pdf_mark_record(pdf_file_t *file, pdf_mark_t *marker);

/*
 * pdf_seek_record
 *
 * Reads a previously marked record from the file again. The marker 
 * needs to have been acquired via a previous call to pdf_mark_record().
 * On return, the input file and the current record (the marked one)
 * are in the same state as on return from pdf_read_record() the first
 * time the record was read from the file.
 *
 * The file must be an input file, but it can be memory-mapped or not.
 *
 * Returns 0 if successful, or sets errno and returns
 * a descriptive error-code on error.
 */
extern pdf_status_t pdf_seek_record(pdf_file_t *file, pdf_mark_t marker);

/*
 * pdf_record_name
 *
 * Provides the name of the record that was last read from the file.
 *
 * Returns 0 if successful, or sets errno and returns
 * a descriptive error-code on error.
 */
extern pdf_status_t pdf_record_name(pdf_file_t *file, char **name);

/*
 * pdf_field
 * 
 * Copies into the location referenced by the last argument
 * the value of the specified field.  The value is taken from
 * the last record read by pdf_read_record(). 
 * 
 * The destination location must be the address of application
 * memory, such as a variable of a matching data type: 
 * 	- For a PDF_SCALAR or PDF_VSIZE field, the variable must 
 * 	  have the same size as the field.
 * 	- For PDF_ARRAY or PDF_VARRAY fields, the location argument must be a 
 * 	  pointer to the correct base type; the pointer value references a 
 * 	  read-only buffer controlled by the file data. If the PDF_READ_WRITE
 *	  flag was passed to pdf_read_header, the pointer value references
 *	  the writeable memory-mapped file, so the array can be modified.
 * 
 * Returns 0 if successful, or sets errno and returns 
 * a descriptive error-code on error.
 */
extern pdf_status_t pdf_field(pdf_file_t *file,
			      const char *field_name,
			      void *value);

/*
 * pdf_fields
 *
 * Like pdf_field(), but extracts the value of each field named in 
 * the string array, which is terminated by a NULL pointer.
 * There must be one destination argument for each field requested.
 *
 * Returns 0 if successful, or sets errno and returns 
 * a descriptive error-code on error.
 */
extern pdf_status_t pdf_fields(pdf_file_t *file,
			       const char **field_names,
			       ...);

/*
 * pdf_update_field
 *
 * Modifies the value of a PDF_SCALAR field in an input file that was
 * opened read-write (O_RDWR in open) and memory-mapped read-write
 * (PDF_READ_WRITE in pdf_read_header). This function will cause a
 * segmentation fault if called for a read-only file.
 *
 * PDF_ARRAY and PDF_VARRAY (including the PDF_STRING type) fields may
 * be updated by modifying the mapped file directly, using the pointer
 * returned by pdf_field() or pdf_fields(). 
 *
 * PDF_VSIZE fields can not be updated, to avoid changing the dimensions
 * of the associated PDF_VARRAY fields and the size of the record. To change
 * dimensions, an output file may be opened and each new record written to it.
 *
 * Returns 0 if successful, or sets errno and returns 
 * a descriptive error-code on error.
 */
extern pdf_status_t pdf_update_field(pdf_file_t *file,
			             const char *field_name,
			             void *value);

/*
 * pdf_dimension
 *
 * Returns the dimension of the named array field in the 
 * last record read by pdf_read_record().
 * Returns 0 if successful, or sets errno and returns
 * a descriptive error-code on error.
 */
extern pdf_status_t pdf_dimension(pdf_file_t *file,
                          const char *field_name,
                          unsigned long *dimension);

/* Consumer routines for getting info about the file, its records, and their 
 * fields.
 */

/*
 * pdf_flags
 *
 * Provides the flags specified when pdf_write_header() created the file.
 * The flags indicate whether PDF_ALIGN was selected by the producer.
 *
 * Returns 0 if successful, or sets errno and returns 
 * a descriptive error-code on error.
 */
extern pdf_status_t pdf_flags(pdf_file_t *file,int *flags);

/*
 * pdf_record_names
 *
 * Provides the names of all record descriptors in the file.
 * The returned string array is terminated by a NULL pointer.
 * The returned string array contains only the terminating NULL pointer
 * if the file has no record types. The array and strings are read-only.
 *
 * Returns 0 if successful, or sets errno and returns
 * a descriptive error-code on error.
 */
extern pdf_status_t pdf_record_names(pdf_file_t *file, char ***names);

/*
 * pdf_record_desc
 *
 * Provides record format information stored in the PDF file, for the
 * named record, e.g. one of the strings returned by pdf_record_names().
 * Returns the information in an array of pdf_record_t structures, like that 
 * input by the producer.
 * The information can be used to determine the types of records and fields
 * that are stored in the file and their attributes.
 *
 * Returns 0 if successful, or sets errno and returns 
 * a descriptive error-code on error.
 */
extern pdf_status_t pdf_record_desc(pdf_file_t *file,
                           	    const char *record_name,
                           	    pdf_record_t **record_desc);

/*
 * pdf_file_attr_names
 *
 * Provides the names of all file-attributes of the file.
 * The returned string array is terminated by a NULL pointer.
 * The returned string array contains only the terminating NULL pointer
 * if the file has no file-attributes. The array and strings are read-only.
 * 
 * Returns 0 if successful, or sets errno and returns
 * a descriptive error-code on error.
 */
extern pdf_status_t pdf_file_attr_names(pdf_file_t *file, char ***names);

/*
 * pdf_file_attr_type
 *
 * Provides the data-type of the named file-attribute.
 * Returns 0 on success. Sets errno and returns 
 * a descriptive error-code on error, including 
 * a request for a non-existent attribute: PDF_ATTRIBUTE_NAME.
 */
extern pdf_status_t pdf_file_attr_type(pdf_file_t *file,
                                       const char *attr_name,
				       pdf_type_t *type);

/*
 * pdf_file_attr_value
 *
 * Provides the value of the named file-attribute. The last argument
 * must point to a variable that matches the data-type of that attribute.
 *
 * Returns 0 if successful, or sets errno and returns
 * a descriptive error-code on error.
 */
extern pdf_status_t pdf_file_attr_value(pdf_file_t *file,
                                        const char *attr_name,
				        void *attr_value);
/*
 * pdf_record_attr_type
 *
 * Provides the data-type of the named record-attribute.
 * Returns 0 on success. Sets errno and returns 
 * a descriptive error-code on error, including a request for a
 * non-existent attribute: PDF_ATTRIBUTE_NAME.
 */
extern pdf_status_t pdf_record_attr_type(pdf_file_t *file,
				 const char *record_name,
				 const char *attr_name,
				 pdf_type_t *type);
/*
 * pdf_record_attr_value
 *
 * Provides the value of the named record-attribute. The last argument
 * must point to a variable that matches the data-type of that attribute.
 *
 * Returns 0 if successful, or sets errno and returns
 * a descriptive error-code on error.
 */
extern pdf_status_t pdf_record_attr_value(pdf_file_t *file,
					  const char *record_name,
					  const char *attr_name,
					  void *attr_value);
/*
 * pdf_field_attr_type
 *
 * Provides the data-type of the named field-attribute.
 * Returns 0 on success. Sets errno and returns 
 * a descriptive error-code on error, including a request for a
 * non-existent attribute: PDF_ATTRIBUTE_NAME.
 */
extern pdf_status_t pdf_field_attr_type(pdf_file_t *file,
				const char *record_name,
				const char *field_name,
				const char *attr_name,
				pdf_type_t *type);

/*
 * pdf_field_attr_value
 *
 * Provides the value of the named field-attribute. The last argument
 * must point to a variable that matches the data-type of that attribute.
 *
 * Returns 0 if successful, or sets errno and returns
 * a descriptive error-code on error.
 */
extern pdf_status_t pdf_field_attr_value(pdf_file_t *file,
					 const char *record_name,
					 const char *field_name,
					 const char *attr_name,
					 void *attr_value);
/*
 * pdf_field_type
 *
 * Returns the data-type of the named field in the specified record, and
 * the kind of field it is (scalar, array, array-size, etc).  A positive
 * value returned for definition_type is the dimension of a fixed length
 * array.  Negative values are used for all other qualifiers, e.g. PDF_SCALAR.
 * Use pdf_field(s) to obtain the field value.
 * Returns 0 if successful, or sets errno and returns
 * a descriptive error-code on error.
 */
extern pdf_status_t pdf_field_type(pdf_file_t *file,
			  const char *record_name,
                          const char *field_name,
			  pdf_type_t *type,
			  pdf_def_t  *definition_type);


/* 
 * Common routines for producers and consumers.
 */

/*
 * pdf_close
 *
 * Cleans up a file that has been read or written.  The file descriptor
 * is not closed.
 *
 * Returns 0 if successful, or sets errno and returns 
 * a descriptive error-code on error.
 */
extern pdf_status_t pdf_close(pdf_file_t *file);



/*
 *
 * Macros for determining Alpha versions and base families.
 * These can be used to process "pdf_processor_type" values.
 *
 */

extern int __alpha_family[];

/* This macro will evaluate to a base EV<n>_CPU constant from cpuconf.h */
#define  ALPHA_FAMILY(proc_type) (__alpha_family[(proc_type)&0xffffffff])

#define IN_EV4_FAMILY(proc_type) (ALPHA_FAMILY(proc_type) == EV4_CPU)
#define IN_EV5_FAMILY(proc_type) (ALPHA_FAMILY(proc_type) == EV5_CPU)
#define IN_EV6_FAMILY(proc_type) (ALPHA_FAMILY(proc_type) == EV6_CPU)



#ifdef __cplusplus        
}                          
#endif                      

#endif /* _CMPLRS_PDF_H_ */
