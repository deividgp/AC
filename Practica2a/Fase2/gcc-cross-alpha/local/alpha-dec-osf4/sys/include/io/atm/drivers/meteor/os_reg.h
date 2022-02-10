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
#pragma ident "@(#)$RCSfile: os_reg.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1997/08/28 16:25:53 $"

#ifndef _OS_REG_H_
#define _OS_REG_H_

/*
* Module Name:
*   os_reg.h
*   
* Abstract:
*   This is the interface for register functions, memory functions,
*   timer function, and generic utilities that must be provided 
*   by the OS.
*
* Authors:
*   NCD  -  Nancy C. DiFonzo
*
* Modification History:
*   Date       Name  Description 
*   15-Mar-96  NCD   Created
*   27-Mar-96  NCD   - Modified the input reg parameter for all routines 
*                      to be the offset, not pointers to the offsets.
*                    - General modifications based on first pass of internal
*                      review.
*
* Description:
*   There will be one instantiation of this module for each adapter in the 
*   system.
*/

#include <sys/malloc.h>


/*++
* ==============
* = os_reg_set =
* ==============
*
* Overview:
*   Writes the specified longword value to the specified adapter register.
*
* Arguments:
*  os_reg_handle - (IN) The handle returned from os_reg_create.
*
*  p_reg         - (IN) Pointer to register to write.  Note that this pointer
*                       is a longword offset into PCI Memory Space.
*
*  value         - (IN) Longword value to write to the register.
*
* Returns:
*   None
*
* Preconditions:
*   - os_reg_create has been called
*   
* Postconditions:
*   The value of the specified register is set
--*/
void os_reg_set (HANDLE   os_reg_handle,
                 UINT32   reg,
                 UINT32   value);



/*++
* ==============
* = os_reg_get =
* ==============
*
* Overview:
*   Reads the contents of the specified longword adapter register.
*
* Arguments:
*  os_reg_handle  - (IN)  The value that was returned by os_reg_create.
*
*  reg            - (IN)  The PCI memory space longword offset for 
*                         this register.
*
* Returns:
*   The value of the register.
*
* Preconditions:
*   - os_reg_create has been called.
*
* Postconditions:
*   None
--*/

UINT32 os_reg_get (HANDLE   os_reg_handle, 
                   UINT32   reg);
            

/*++
* ==============
* = os_pci_get =
* ==============
*
* Overview:
*   Reads data from the PCI configuration area.
*
* Arguments:
*  os_reg_handle  - (IN)  The value that was returned by os_reg_create.
*
*  reg            - (IN)  The PCI config space offset for this
*                         location.
*  
*  size           - (IN)  Size (in bytes) of data to be read.
*
* Returns:
*   The value of the PCI location.
*
* Preconditions:
*   - os_reg_create has been called.
*
* Postconditions:
*   None
--*/

UINT32 os_pci_get (HANDLE   os_reg_handle, 
                   UINT32   reg,
                   UINT32   size);

/*++
* ============
* = os_delay =
* ============
*
* Overview:
*   Delays the specified number of microseconds.  This should not be called
*   often or with large values.  In most implementations, the processor
*   enters a tight software loop.
*
* Arguments:
*  os_handle - (IN)  The handle returned from os_create.
*
*  delay     - (IN)  The number of microseconds to delay.
*
* Returns:
*   none
*
* Preconditions:
*   none
*
* Postconditions:
*   A small amount of time may have passed.
--*/

void os_delay (HANDLE os_handle,
               UINT32 delay);

/*++
* ----------------------
* - LPA_TIMER_CALLBACK -
* ----------------------
*
* Overview:
*   Routine that is called when a timer expires.
*
* Arguments:
*   context - (IN) The value that was specified when the timer was allocated.
*   
* Returns:
*   none
*
* Preconditions:
*   None
*
* Postconditions:
*   none
--*/

typedef void (*LPA_TIMER_CALLBACK) (HANDLE context);

/*++
* ==================
* = lpa_timer_alloc =
* ==================
*
* Overview:
*   Allocates and initializes a timer.  Some implementations of this
*   routine may allocate memory or other resources.  This routine can be
*   called from the coded path that processes receives or "transmit dones"
*   (which may include interrupt level for some operating systems).
*
* Arguments:
*  os_handle      - (IN)  The handle returned from os_create.
*
*  callback       - (IN)  Pointer to the routine to callback when the timer
*                         expires.
*
*  context        - (IN)  Value to pass to the callback routine.
*
*  p_timer_handle - (OUT) Pointer to a timer handle.  This value must be used
*                         when setting, canceling, or deallocating a timer.
*                         It will have the os_handle associated with it so that
*                         if the timer is specified in a call, the os_handle
*                         does not also need to be specified.
* Returns:
*   STATUS_K_SUCCESS   - Timer was successfully allocated
*   STATUS_K_RESOURCES - Timer was NOT allocated.
*
* Preconditions:
*   none
*
* Postconditions:
*   A timer may have been allocated.
--*/

STATUS lpa_timer_alloc (HANDLE             os_handle,
			LPA_TIMER_CALLBACK callback,
			HANDLE             context,
			HANDLE            *p_timer_handle);
/*++
* ================
* = lpa_timer_set =
* ================
*
* Overview:
*   Sets a timer to expire after a specified time.  When the timer expires,
*   its associated callback routine is called.
*
* Arguments:
*  timer_handle - (IN)  The value returned from lpa_timer_alloc.
*
*  time         - (IN)  Number of milliseconds until the callback is called.
*
* Returns:
*   STATUS_K_SUCCESS
*   STATUS_K_FAILURE
*
* Preconditions:
*   - The timer was allocated.
*
* Postconditions:
*   A timer is set.                    
--*/

STATUS lpa_timer_set (HANDLE timer_handle,
		      UINT32  time);

/*++
* ===================
* = lpa_timer_cancel =
* ===================
*
* Overview:
*   Cancels the specified timer.   The timer callback routine is guaranteed
*   not be called after this routine completes.  Also, it is permissible to
*   cancel a timer that has not been set.
*
* Arguments:
*  timer_handle - (IN)  The value returned from lpa_timer_alloc.
*
* Returns:
*   STATUS_K_SUCCESS       - Timer was successfully canceled.
*
*   STATUS_K_NO_WORK_TO_DO - Timer was not set.
*
* Preconditions:
*   - The timer was allocated.
*
* Postconditions:
*   - The timer is canceled.
*   - The timer callback will not be called.                    
--*/

STATUS lpa_timer_cancel (HANDLE timer_handle);


/*++
* ====================
* = lpa_timer_dealloc =
* ====================
*
* Overview:
*   Deallocates the specified timer.  Even though some implementations may not 
*   support this feature, it must be called.  Note that this routine can be
*   called even if the timer has been started, but not yet expired.
*
*   After this routine completes, it is guaranteed that the timer callback will
*   not be called.
*
* Arguments:
*  timer_handle - (IN)  The value returned from lpa_timer_alloc.
*
* Returns:
*   none
*
* Preconditions:
*   - The timer was allocated.
*
* Postconditions:
*   - A timer was deallocated
*   - The timer callback will not be called.
--*/

void lpa_timer_dealloc (HANDLE timer_handle);

/*++
* =================
* = lpa_field_get =
* =================
*
* Overview:
*   Extracts a field from a value based on a mask which contains 1's in all
*   bit positions of the field.  The extracted field is right-justified and
*   returned.
*
*   For example, if field_value = 0x00123400, and field_mask = 0x00FFFF00, then
*   the value 0x1234 is returned.
*
* Arguments:
*   value       - (IN) The value from which to extract the field.
* 
*   field_mask  - (IN) The mask of the field to extract.
*              
* Returns:
*   The specified field right justified. If the field mask is 0, then the value
*   0 is returned.
*
* Preconditions:
*   None
*
* Postconditions:
*   None
--*/

UINT32 lpa_field_get (UINT32 field_value, UINT32 field_mask);


/*++
* =================
* = lpa_field_set =
* =================
*
* Overview:
*   Sets the contents of a field in a value.  All other fields of the value
*   are left untouched.
*
* Arguments:
*   p_value     - (IO) Pointer to the value containing the field to update.
* 
*   field_mask  - (IN) The mask of the field to update.
*              
*   field_value - (IN) The new value of the field.
* 
* Returns:
*   None
*
* Preconditions:
*   The right-justified field_value must fit into field_mask.
*
* Postconditions:
*   None
--*/

void lpa_field_set (UINT32 *p_value, UINT32 field_mask, UINT32 field_value);

/*++
* ================
* = lpa_in_range =
* ================
*
* Overview:
*   Checks if the specified value is inclusively within a range of two
*   values.
*
* Arguments:
*   value - (IN) Value to check.
* 
*   min   - (IN) The minimum acceptable value.
*              
*   max   - (IN) The maximum acceptable value.
* 
* Returns:
*   TRUE
*   FALSE
*
* Preconditions:
*   None
*
* Postconditions:
*   None
--*/

BOOLEAN lpa_in_range (UINT32 value, UINT32 min, UINT32 max);


/* LPA_SIMPLE_LIST
 *
 *  LPA_SIMPLE_LIST is a macro that creates a list of elements of a certain type.
 *  The macro has two arguments:
 *
 *      type    - The data type for elements that will be stored in the list.
 *      name    - The name of the resulting list type.  
 *
 *  For a structure to be stored in a simple list, its first member must be a
 *  pointer to that same kind of structure.  For example, a list of names
 *  would use a structure like the following:
 *
 *      struct name_tag
 *         {
 *         struct name_tag *p_next;
 *         char            *text;
 *         } NAME_RECORD;
 *
 *  To create a type for a simple list of names, the following declaration
 *  can be used:
 *
 *      LPA_SIMPLE_LIST (NAME_RECORD, NAME_LIST);
 *
 *  NAME_LIST is now a type for a list of elements of type NAME_RECORD.  An
 *  example of its usage is:
 *
 *      NAME_LIST   list_of_names;
 *
 */
#define LPA_SIMPLE_LIST(type, name) typedef struct     \
                                       {               \
                                       type   *p_root; \
                                       type   *p_tmp;  \
                                       type   *p_ptr;  \
                                       int     size;   \
                                       } name

/*++
* =========================
* = lpa_list_init (macro) =
* =========================
*
* Overview:
*   Initializes an instance of a simple list.  Simple lists MUST be
*   initialized before they can be used for any other purpose.
*
* Arguments:
*   list    - (IO) Simple List to be initialized.
* 
* Returns:
*   None
*
* Preconditions:
*   None
*
* Postconditions:
*   The simple list contains zero entries.
--*/
#define lpa_list_init(list) \
   {                        \
   (list).p_root = NULL;    \
   (list).size   = 0;       \
   }

/*++
* ========================
* = lpa_list_add (macro) =
* ========================
*
* Overview:
*   Adds a single element to a simple list.  The element is added to the
*   head of the list.
*
* Arguments:
*   list        - (IO) Simple list to be modified (not a pointer to the list).
*   p_element   - (IN) Pointer to the element that is to be added to the list.
* 
* Returns:
*   None
*
* Preconditions:
*   None
*
* Postconditions:
*   The element is a member of the list.
*
*   The size of the list stored in the list header has been incremented by one.
--*/
#define lpa_list_add(list, p_element)   \
   {                                    \
   (p_element)->p_next = (list).p_root; \
   (list).p_root       = p_element;     \
   (list).size        += 1;             \
   }

/*++
* =================================
* = lpa_list_insert_after (macro) =
* =================================
*
* Overview:
*   Adds a single element to a simple list.  The element is inserted after
*   a specified key element.
*
* Usage:
*   This macro may be used to insert an element into an ordered list.
*   The following is an example of such an application:
*
*       typedef struct _int_tag
*          {
*          struct _int_tag  *p_next;
*          int               data;
*          } INT_RECORD;
*
*       LPA_SIMPLE_LIST (INT_RECORD, INT_LIST);
*       .
*       .
*       .
*       INT_RECORD  *p_current, *p_prev;
*       INT_LIST    int_list
*
*       p_prev = NULL;
*       lpa_list_traverse (int_list, p_current);
*          {
*          if (p_new_data->data <= p_current->data)
*             {
*             lpa_list_insert_after (int_list, p_prev, p_new_data);
*             break;
*             }
*          p_prev = p_current;
*          }
*       if (p_current == NULL)
*          lpa_list_insert_after (int_list, p_prev, p_new_data);
*
* Arguments:
*   list        - (IO) Simple list to be modified (not a pointer to the list).
*   p_key       - (IN) Pointer to the key element.
*   p_element   - (IN) Pointer to the element that is to be added to the list.
* 
* Returns:
*   None
*
* Preconditions:
*   p_key points to an element that is a member of the list or is NULL.
*
* Postconditions:
*   The element is a member of the list and directly follows the key element.
*   If the key pointer is NULL, the new element is at the head of the list.
*
*   The size of the list stored in the list header has been incremented by one.
--*/
#define lpa_list_insert_after(list, p_key, p_element) \
   {                                                  \
   if ((p_key) == NULL)                               \
      {                                               \
      (p_element)->p_next = (list).p_root;            \
      (list).p_root       = (p_element);              \
      }                                               \
   else                                               \
      {                                               \
      (p_element)->p_next = (p_key)->p_next;          \
      (p_key)->p_next     = (p_element);              \
      }                                               \
   (list).size        += 1;                           \
   }

/*++
* ===========================
* = lpa_list_delete (macro) =
* ===========================
*
* Overview:
*   Deletes a single element from a simple list.  The element to be deleted
*   is identified by its address.
*
* Arguments:
*   list        - (IO) Simple list to be modified.
*   p_element   - (IN) Pointer to the element that is to be removed from
*                      the list.
*
* Returns:
*   None
*
* Preconditions:
*   None
*
* Postconditions:
*   The element is a not member of the list.
*
*   If the element was a member of the list, the size of the list has been
*   decremented  by one.  Otherwise, nothing happens.
--*/
#define lpa_list_delete(list, p_element)                                     \
	{                                                                         \
	if ((list).p_root == p_element)                                           \
		{                                                                      \
		/* First, handle the case in which the element to be deleted is at */  \
		/* the root of the list.                                           */  \
		(list).p_root = (p_element)->p_next;                                   \
		(list).size  -= 1;                                                     \
		}                                                                      \
	else                                                                      \
		{                                                                      \
		/* Handle the case in which the element to be deleted is deeper */     \
		/* into the list than the root element.                         */     \
		(list).p_tmp = (list).p_root;                                          \
		while (((list).p_tmp != NULL) && ((list).p_tmp->p_next != p_element))  \
			(list).p_tmp = (list).p_tmp->p_next;                                \
																									  \
		/* If the target element has been found (not the end of the list), */  \
		/* unlink the target element and decrement the size by 1.          */  \
		if ((list).p_tmp != NULL)                                              \
			{                                                                   \
			(list).p_tmp->p_next = (p_element)->p_next;                         \
			(list).size         -= 1;                                           \
			}                                                                   \
		}                                                                      \
	}

/*++
* =============================
* = lpa_list_find_del (macro) =
* =============================
*
* Overview:
*   Removes a single element from a simple list.  The element to be removed
*   is identified by its address. If the element is found on the list is
*   found "found" is set to TRUE, if not it is set to FALSE.
*
* Arguments:
*   list        - (IO)  Simple list to be modified.
*   p_element   - (IN)  Pointer to the element that is to be removed from
*                       the list.
*   found       - (OUT) TRUE iff the element on the list is found.
*
* Returns:
*   None
*
* Preconditions:
*   None
*
* Postconditions:
*   The element is a not member of the list.
*
*   If the element was a member of the list, the size of the list has been
*   decremented  by one.  Otherwise, nothing happens.
--*/

#define lpa_list_find_del(list, p_element, found)                                     \
	{                                                                         \
	if ((list).p_root == p_element)                                           \
		{                                                                      \
		/* First, handle the case in which the element to be deleted is at */  \
		/* the root of the list.                                           */  \
		(list).p_root = (p_element)->p_next;                                   \
		(list).size  -= 1;                                                     \
		found = TRUE;                                                          \
		}                                                                      \
	else                                                                      \
		{                                                                      \
		/* Handle the case in which the element to be deleted is deeper */     \
		/* into the list than the root element.                         */     \
		(list).p_tmp = (list).p_root;                                          \
		while (((list).p_tmp != NULL) && ((list).p_tmp->p_next != p_element))  \
			(list).p_tmp = (list).p_tmp->p_next;                                \
																									  \
		/* If the target element has been found (not the end of the list), */  \
		/* unlink the target element and decrement the size by 1.          */  \
		if ((list).p_tmp != NULL)                                              \
			{                                                                   \
			(list).p_tmp->p_next = (p_element)->p_next;                         \
			(list).size         -= 1;                                           \
			found = TRUE;                                                       \
			}                                                                   \
		else                                                                   \
			{                                                                   \
			found = FALSE;                                                      \
			}                                                                   \
		}                                                                      \
	}

/*++
* =============================
* = lpa_list_traverse (macro) =
* =============================
*
* Overview:
*   Allows a simple list to be easily traversed.  This macro is not in the
*   form of a function but in the form of a loop.
*
* Usage:
*   The lpa_list_traverse macro should be used as a loop construct much like
*   a 'for' loop is used.  lpa_list_traverse must be followed by a statement
*   or bracketed group of statements.  For example:
*
*       NAME_LIST    name_list;
*       NAME_RECORD *p_name_record;
*
*       printf ("Names in the List:\n");
*       lpa_list_traverse (name_list, p_name_record)
*          {
*          printf ("  %s\n", p_name_record->text);
*          }
*
*   Note that if the list is empty, the body of the loop will not execute.
*
*   Do NOT use the lpa_list_traverse macro to iteratively deallocate all of
*   the elements in the list!  Use the lpa_list_dealloc macro for this.
*
* Arguments:
*   list    - (IN)  The simple list to be traversed.
*
*   p_index - (OUT) The loop index.  This is a pointer to the structure stored
*                   in the list.  The loop executes once for each element
*                   in the list and the p_index points to the element being
*                   processed for each iteration.
* 
* Returns:
*   Not Applicable
*
* Preconditions:
*   None
*
* Postconditions:
*   None
--*/
#define lpa_list_traverse(list, p_index) for (p_index = (list).p_root,       \
                                              (list).p_ptr = (p_index) ?     \
                                                 (p_index)->p_next : NULL;   \
                                              p_index != NULL;               \
                                              p_index  = (list).p_ptr,       \
                                              (list).p_ptr = (p_index) ?     \
                                                 (p_index)->p_next : NULL    \
                                             )

/*++
* ============================
* = lpa_list_dealloc (macro) =
* ============================
*
* Overview:
*   Delete and deallocate (using os_mem_dealloc) all elements in the simple
*   list.
*
*   Note that if the list elements contain pointers to allocated data, this
*   data will be lost.  First use lpa_list_traverse to deallocate all pointers
*   within the element structure.  Use lpa_list_dealloc to deallocate the
*   actual element structures within the list.
*
* Arguments:
*   os_handle  - (IN)  Handle of the appropriate os instance.
*   list       - (IN)  Simple list to be cleared.
* 
* Returns:
*   Not Applicable
*
* Preconditions:
*   None
*
* Postconditions:
*   The list is empty and each element has been deallocated.
--*/
#define lpa_list_dealloc(os_handle, list)       \
   {                                            \
   while ((list).p_root)                        \
      {                                         \
      (list).p_tmp  = (list).p_root;            \
      (list).p_root = (list).p_root->p_next;    \
      FREE ((list).p_tmp, M_DEVBUF); 		\
      (list).size  -= 1;                        \
      }                                         \
   }



#endif	/* _OS_REG_H_ */

