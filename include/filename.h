/**
 * @file    filename.h
 * @author  benjaimn gerard <ben@sashipa.com>
 * @date    2002/09/30
 * @brief   filename utilities.
 *
 * $Id: filename.h,v 1.1 2002-09-30 20:03:02 benjihan Exp $
 */

#ifndef _FILENAME_H_
#define _FILENAME_H_

#include "extern_def.h"

DCPLAYA_EXTERN_C_START

/** Get extension from file path.
 *
 * @param  pathname  File path name
 *
 * @return Pointer to extension in pathname. Address of `.' char.
 * @retval !0  Extension found.
 * @retval  0  Extension not found.
 */
const char *fn_ext(const char *pathname);

/** Get basename (or leafname) of a path.
 *
 *    The fn_basename() function returns a pointer to the next character after
 *    the last '/' or pathname if there is no '/' character.
 *
 * @param  pathname  File path name to get its basename.  
 *
 * @return pointer to first leafname character in pathname.
 * @retval 0  Error.
 */
const char *fn_basename(const char *pathname);

/** Alias for the fn_basename() function. */
const char * fn_leafname(const char * pathname);

/** Test if a path is absolute.
 *
 *    The fn_is_absolute() function tests if the first charactere of pathname
 *    is a '/'.
 *
 * @param  pathname  A file path name.
 *
 * @retval  0  Path is relative (no starting '/').
 * @retval  1  Path is absolute (starting '/').
 *
 * @see fn_is_relative()
 */
int fn_is_absolute(const char *pathname);

/** Test if a path is relative.
 *
 *    The fn_is_relative() function tests if the first charactere of pathname
 *    is a not '/'.
 *
 * @param  pathname  A file path name.
 *
 * @retval  1  Path is relative (no starting '/').
 * @retval  0  Path is absolute (starting '/').
 *
 * @see fn_is_absolute()
 */
int fn_is_relative(const char * pathname);

/** Copy a pathname to a buffer and remove trailing '/'.
 *
 *    The fn_get_path() function copies a pathname to a buffer, removes
 *    trailing '/', translates '\' to '/' an returns a pointer to the 
 *    null terminator character in path. If not null isslash is set to 1
 *    or 0 respectively if pathname is '/' terminated or not.
 *
 * @param  path      Destination path buffer.
 * @param  pathname  Path name to copy.
 * @param  max       Size of path buffer.
 * @param  isslash   Optionnal '/' terminator watcher.
 *
 * @return Pointer to the null terminator in path buffer.
 * @retval 0  Error. Bad parameters or buffer overflow.
 */
char * fn_get_path(char *path, const char *pathname, int max, int * isslash);

/** Append a leafname to a path.
 *
 *    The fn_add_path() function appends a relative path (leafname) to a path.
 *    The path must not be '/' terminated like path created by fn_get_path().
 *    The optionnal pathend parameter must point to the 0 trailing character.
 *    The pathend parameter couls be null. In that case the function will
 *    calculate it. This function translates leafname '\' to '/' while copying.
 *
 * @param  path      path where leafname will be append without terminator.
 * @param  pathend   0 or pointer to path terminator character.
 * @param  leafname  Relative path to append (no '/' at start).
 * @param  max       Size of path buffer.
 *
 * @return pointer to final path terminator (null character).
 * @retval 0  Error. Bad parameters or buffer overflow.
 */
char * fn_add_path(char *path, char *pathend, const char *leafname, int max);

DCPLAYA_EXTERN_C_END

#endif /* #define _FILENAME_H_ */