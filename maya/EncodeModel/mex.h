#pragma once
/*
* @(#)mex.h    generated by: makeheader    Mon Sep  4 03:57:16 2000
*
*		built from:	../include/copyright.h
*				mex_typedefs.h
*				fmexapi.c
*				globals.c
*				mexapi.c
*				mexapiv4.c
*				mexcbk.c
*				mexintrf.c
*				modver/modver.c

%MEX   Compile MEX-function
%
%   Usage:
%       mex [options ...] file [files ...]
%
%   Description:
%       MEX compiles and links source files into a shared library called a
%       MEX-file, executable from within MATLAB. It also builds executable
%       files for standalone MATLAB engine and MAT-file applications.
%
%   Command Line Options Available on All Platforms:
%       -c
%           Compile only. Creates an object file but not a MEX-file.
%       -client engine
%           Build standalone MATLAB engine or MAT-file application.
%       -compatibleArrayDims
%           Build a MEX-file using the MATLAB Version 7.2 array-handling
%           API, which limits arrays to 2^31-1 elements. This option is the
%           default, but in the future the -largeArrayDims option will be
%           the default.
%       -D<name>
%           Define a symbol name to the C preprocessor. Equivalent to a
%           "#define <name>" directive in the source. Do not add a space
%           after this switch.
%       -D<name>=<value>
%           Define a symbol name and value to the C preprocessor. Equivalent
%           to a "#define <name> <value>" directive in the source. Do not
%           add a space after this switch.
%       -f <optionsfile>
%           For advanced users. Specify location and name of the MEX
%           configuration file to use. Overrides MEX's default compiler
%           selection mechanism.
%       -g
%           Create a MEX-file containing additional symbolic information for
%           use in debugging. This option disables MEX's default behavior of
%           optimizing built object code (see the -O option).
%       -h[elp]
%           Display this message.
%       -I<pathname>
%           Add <pathname> to the list of directories to search for #include
%           files. Do not add a space after this switch.
%       -l<name>
%           Link with object library. On Windows, <name> expands to
%           "<name>.lib" or "lib<name>.lib". On Linux, to "lib<name>.so".
%           On Mac, to "lib<name>.dylib". Do not add a space after this
%           switch.
%       -L<folder>
%           Add <folder> to the list of folders to search for
%           libraries specified with the -l option. Do not add a space
%           after this switch.
%       -largeArrayDims
%           Build a MEX-file using the MATLAB large-array-handling API. This
%           API can handle arrays with more than 2^31-1 elements when
%           compiled on 64-bit platforms. -compatibleArrayDims is the
%           default option.
%       -n
%           No execute mode. Display commands that MEX would otherwise
%           have executed, but do not actually execute any of them.
%       -O
%           Optimize the object code. Optimization is enabled by default and
%           by including this option on the command line. If the -g option
%           appears without the -O option, optimization is disabled.
%       -outdir <dirname>
%           Place all output files in folder <dirname>.
%       -output <resultname>
%           Create MEX-file named <resultname>. The appropriate MEX-file
%           extension is automatically appended. Overrides MEX's default
%           MEX-file naming mechanism.
%       -setup <lang>
%           Change the default compiler to build <lang> language MEX-files.
%           When this option is specified, no other command line
%           input is accepted.
%       -silent
%           Suppress informational messages. The mex function still reports
%           errors and warnings, even when you specify -silent.
%       -U<name>
%           Remove any initial definition of the C preprocessor symbol
%           <name>. (Inverse of the -D option.) Do not add a space after
%           this switch.
%       -v
%           Verbose mode. Display the values for important internal
%           variables after all command line arguments are considered.
%           Displays each compile step and final link step fully evaluated.
%       <name>=<value>
%           Override default setting for variable <name>. This option is
%           processed after all command line arguments are considered.
%
%   Command Line Options Available Only on Windows Platforms:
%       @<rspfile>
%           Include contents of the text file <rspfile> as command line
%           arguments to MEX.
%
%   For more information, see
%           http://www.mathworks.com/help/matlab/ref/mex.html

% Copyright 1984-2013 The MathWorks, Inc.
% This is an autogenerated file.  Do not modify.
% Built-in function.

*/


#ifndef mex_h
#define mex_h


/* $Revision: 1.3 $ */
/*
* Copyright (c) 1984-2000 The MathWorks, Inc.
* All Rights Reserved.
*/



/* $Revision: 1.4 $ */
#ifndef mex_typedefs_h
#define mex_typedefs_h
typedef struct impl_info_tag *MEX_impl_info;

#include "matrix.h"

typedef struct mexGlobalTableEntry_Tag
{
	const char *name;             /* The name of the global */
	mxArray    **variable;        /* A pointer to the variable */
} mexGlobalTableEntry, *mexGlobalTable;

typedef struct mexFunctionTableEntry_tag {
	const char *  name;
	mxFunctionPtr f;
	int           nargin;
	int           nargout;
	struct _mexLocalFunctionTable *local_function_table;
} mexFunctionTableEntry, *mexFunctionTable;

typedef struct _mexLocalFunctionTable {
	size_t           length;
	mexFunctionTable entries;
} _mexLocalFunctionTable, *mexLocalFunctionTable;

typedef struct {
	void(*initialize)(void);
	void(*terminate)(void);
} _mexInitTermTableEntry, *mexInitTermTableEntry;

#define MEX_INFORMATION_VERSION 1

typedef struct {
	int                   version;
	int                   file_function_table_length;
	mexFunctionTable      file_function_table;
	int                   global_variable_table_length;
	mexGlobalTable        global_variable_table;
	int                   npaths;
	const char **         paths;
	int                   init_term_table_length;
	mexInitTermTableEntry init_term_table;
} _mex_information, *mex_information;

typedef mex_information(*fn_mex_file)(void);

typedef void(*fn_clean_up_after_error)(void);
typedef const char *(*fn_simple_function_to_string)(mxFunctionPtr f);

typedef fn_clean_up_after_error fn_mex_enter_mex_library;
typedef fn_clean_up_after_error fn_mex_exit_mex_library;

#endif

#ifdef __cplusplus
extern "C" {
#endif


	/*
	* This header file "mex.h" declares all the types, macros and
	* functions necessary to interface mex files with the current
	* version of MATLAB.  See the release notes for information on
	* supporting syntax from earlier versions.
	*/
#include "matrix.h"

#include <stdio.h>

#if defined(applec)
	/* MATLAB is compiled with Metrowerks CodeWarrior C.
	File I/O functions in MPW SC MEX-files are mapped back to MATLAB
	to avoid Data-to-Code Reference link errors from IntEnv.o.
	So, the macros defined in SC's stdio.h which make direct reference
	to the elements of a FILE structure need to be redefined as
	callbacks to MATLAB.
	*/
#undef getc
#undef putc
#undef clearerr
#undef feof
#undef ferror
#endif



	/*
	* mexFunction is the user defined C routine which is called upon invocation
	* of a mex function.
	*/
	void mexFunction(
		int           nlhs,           /* number of expected outputs */
		mxArray       *plhs[],        /* array of pointers to output arguments */
		int           nrhs,           /* number of inputs */
#if !defined(V4_COMPAT)
		const mxArray *prhs[]         /* array of pointers to input arguments */
#else
		mxArray *prhs[]         /* array of pointers to input arguments */
#endif
		);

#if defined (powerc) && defined(__MWERKS__) && defined(MATLAB_MEX_FILE)
#pragma export list mexFunction
#endif


	/*
	* Issue error message and return to MATLAB prompt
	*/
	extern void mexErrMsgTxt(
		const char	*error_msg	/* string with error message */
		);


	/*
	* Issue error message if warnings enabled in MATLAB
	*/
	extern void mexWarnMsgTxt(
		const char	*error_msg	/* string with error message */
		);


	/*
	* mex equivalent to MATLAB's "disp" function
	*/
	extern int mexPrintf(
		const char	*fmt,	/* printf style format */
		...				/* any additional arguments */
		);


	/*
	#define printf mexPrintf
	*/


	/*
	* Remove all components of an array plus the array header itself
	* from MATLAB's memory allocation list.  The array will now
	* persist between calls to the mex function.  To destroy this
	* array, you will need to explicitly call mxDestroyArray().
	*/
	extern void mexMakeArrayPersistent(
		mxArray *pa              /* pointer to array */
		);


	/*
	* Remove memory previously allocated via mxCalloc from MATLAB's
	* memory allocation list.  To free this memory, you will need to
	* explicitly call mxFree().
	*/
	extern void mexMakeMemoryPersistent(void *ptr);


	/*
	* Look up a function and return an opaque handle for use with
	* mexCallMATLABFunction.
	*/
	extern void mexGetFunctionHandle(void);


	/*
	* Call a function whose handle was determined by mexGetFunctionHandle.
	*/
	extern void mexCallMATLABFunction(void);


	/*
	* Register a function pointer as a MATLAB-callable function.
	*/
	extern void mexRegisterFunction(void);


	/*
	* mex equivalent to MATLAB's "set" function
	*/
	extern int mexSet(double handle, const char *property, mxArray *value);


	/* API interface which mimics the "get" function */
	extern const mxArray *mexGet(double handle, const char *property);


	/*
	* call MATLAB function
	*/
	extern int mexCallMATLAB(
		int		nlhs,			/* number of expected outputs */
		mxArray	*plhs[],		/* pointer array to outputs */
		int		nrhs,			/* number of inputs */
		mxArray	*prhs[],		/* pointer array to inputs */
		const char	*fcn_name		/* name of function to execute */
		);


	/*
	* set or clear mexCallMATLAB trap flag (if set then an error in
	* mexCallMATLAB is caught and mexCallMATLAB will return a status value,
	* if not set an error will cause control to revert to MATLAB)
	*/
	extern void mexSetTrapFlag(int flag);


	/*
	* Perform in-place subscript assignment.
	*/
	extern void mexSubsAssign(
		mxArray *plhs, /* pointer to lhs, to be modified in-place */
		const mxArray *sub[], /* array of subscripts for lhs */
		int nsubs,     /* number os subscripts */
		const mxArray *prhs /* pointer to rhs */
		);


	/*
	* Retrieve a specified subset of an array.
	*/
	extern mxArray *mexSubsReference(
		const mxArray *prhs, /* pointer to rhs */
		const mxArray *subs[], /* array of subscripts for rhs */
		int nsubs /* number of subscripts */
		);


	/*
	* Print an assertion-style error message and return control to the
	* MATLAB command line.
	*/
	extern void mexPrintAssertion(
		const char *test,
		const char *fname,
		int linenum,
		const char *message);


	/*
	* mexAddFlops is no longer allowed.
	*/
#define mexAddFlops(x) mexAddFlops_is_obsolete



	/*
	* Tell whether or not a mxArray is in MATLAB's global workspace.
	*/
	extern bool mexIsGlobal(const mxArray *pA);


#if defined(V4_COMPAT)


	/*
	* Easy put copy of the matrix in the local workspace
	* Obsolete: use mxCreateDoubleMatrix() and mexPutArray(parray, "caller")
	* instead
	*/
	extern int mexPutFull(
		char	*name,		/* name of variable in question */
		int		m,		/* number of rows */
		int		n,		/* number of columns */
		double	*pr,		/* real part */
		double	*pi		/* imaginary part */
		);


	/*
	* Easy get copy of the matrix from the local workspace
	* Obsolete: use mexGetArray(name, "caller") and mxGet
	* routines instead
	*/
	extern int mexGetFull(
		char	*name,		/* name of variable in question */
		int		*m,		/* number of rows */
		int		*n,		/* number of columns */
		double	**pr,		/* real part */
		double	**pi		/* imaginary part */
		);


#define mexGetEps   mxGetEps
#define mexGetInf   mxGetInf
#define mexGetNaN   mxGetNaN
#define mexIsFinite mxIsFinite
#define mexIsInf    mxIsInf
#define mexIsNaN    mxIsNaN
#define mexGetGlobal(name)    mexGetArrayPtr(name, "global")
#define mexGetMatrixPtr(name) mexGetArrayPtr(name, "caller")
#define mexGetMatrix(name)    mexGetArray(name, "caller")
#define mexPutMatrix(name)    mexPutArray(name, "caller")
#else
#define mexGetGlobal()    mexGetGlobal_is_obsolete
#define mxSetString()     mxSetString_is_obsolete
#define mxSetDispMode()   mxSetDispMode_is_obsolete
#define mexGetMatrixPtr() mexGetMatrixPtr_is_obsolete
#define mexGetMatrix()    mexGetMatrix_is_obsolete
#define mexPutMatrix()    mexPutMatrix_is_obsolete
#define mexPutFull()      mexPutFull_is_obsolete
#define mexGetFull()      mexGetFull_is_obsolete
#define mexGetEps()       mexGetEps_is_obsolete
#define mexGetInf()       mexGetInf_is_obsolete
#define mexGetNaN()       mexGetNaN_is_obsolete
#define mexIsFinite()     mexIsFinite_is_obsolete
#define mexIsInf()        mexIsInf_is_obsolete
#define mexIsNaN()        mexIsNaN_is_obsolete
#endif /* V4_COMPAT */


	/*
	* Place a copy of the named array into the specified workspace
	*/
	extern int mexPutArray(
		mxArray	*parray,		/* matrix to copy */
		const char *workspace
		);


	/*
	* return a pointer to the named array from the specified workspace
	*/
	extern const mxArray *mexGetArrayPtr(
		const char *name,		/* name of symbol */
		const char *workspace
		);


	/*
	* return a copy of the named array from the specified workspace
	*/
	extern mxArray *mexGetArray(
		const char	*name,		/* name of variable in question */
		const char *workspace
		);


	/*
	* Lock a MEX-function so that it cannot be cleared from memory.
	*/
	extern void mexLock(void);


	/*
	* Unlock a locked MEX-function so that it can be cleared from memory.
	*/
	extern void mexUnlock(void);


	/*
	* Return true if the MEX-function is currently locked, false otherwise.
	*/
	extern bool mexIsLocked(void);


	/*
	* Return the name of a the MEXfunction currently executing.
	*/
	extern const char *mexFunctionName(void);


	/*
	* Parse and execute MATLAB syntax in string.  Returns zero if successful,
	* and a non zero value if an error occurs.
	*/
	extern int mexEvalString(
		const char *str	   /* matlab command string */
		);


	/*
	* Register Mex-file's At-Exit function (accessed via MEX callback)
	*/
	extern int mexAtExit(
		void(*exit_fcn)(void)
		);


	/*
	* clear out MEX-file and free up info structure
	*/
	extern int mexClearMexFile(
		MEX_impl_info info		/* Mex-file implementation-dependent info */
		);


	/*
	* Clear a global of a given name in a workspace.
	*/
	extern void mexClearGlobal(const char *name);

#ifdef __cplusplus
}	/* extern "C" */
#endif

#endif /* mex_h */