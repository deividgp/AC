/* ==================================================================FILE:   Utility.jsDESCR:  Misc. global APIs.NOTES:  ================================================================== *//*DESCR:   Does non-case-sensitive comparison for equality of two URLS,         using only the portion beginning with the filename.PARAMS:  URL1_, URL2_  The URLs.RETURNS: True if equal, false otherwise.NOTES:   Not applicable to nethelp: URLs. Also requires that any fragment         specifier attached to the URLs does not contain "/".*/function URLsSansPathsAreSame( URL1_, URL2_ ){   // Standardize case.   var URL1 = URL1_.toUpperCase()   var URL2 = URL2_.toUpperCase()   // Remove any path.   URL1 = URL1.substring( URL1.lastIndexOf( "/" ) + 1 )   URL2 = URL2.substring( URL2.lastIndexOf( "/" ) + 1 )   // Compare.   return ( URL1 == URL2 )}/*DESCR:   Converts a URL to a simple filename (no path, no trailing         specifiers).PARAMS:  URL  The URL.RETURNS: The converted URL.NOTES:   Not applicable to nethelp: URLs. Also requires that any fragment         specifier attached to the URLs does not contain "/".*/function makeSimpleFilename( URL ){   var filename   // Standardize case.   filename = URL.toLowerCase()   // Remove any path.   filename = filename.substring( filename.lastIndexOf( "/" ) + 1 )   // Remove any specifiers.   if ( filename.indexOf( "#" ) > 0 ) {   	filename = filename.substring( 0, filename.indexOf( "#" ) )   }   if ( filename.indexOf( "?" ) > 0 ) {      filename = filename.substring( 0, filename.indexOf( "?" ) )   }   return filename}/*DESCR:   Runtime error handler.PARAMS:  Standard JS event params.RETURNS: Boolean to optionally supress runtime error dialogs.NOTES:   If ERRS_TO_CONSOLE is ture, sends JS runtime errors to console for         any window that binds this handler. If ERR_DLGS is true, error         dialogs will not be supressed.*/function errHandler( msg, URL, lineNum ){   if ( ERRS_TO_CONSOLE ) {      // Report error to console.      java.lang.System.out.println( "" )      java.lang.System.out.println( "Error:" )      java.lang.System.out.println( msg )      java.lang.System.out.println( URL )      java.lang.System.out.println( lineNum )      java.lang.System.out.println( "" )   }   // Allow or supress runtime error dialogs.   return ( ERR_DLGS ? false : true )}/*DESCR:   Assertion routine.PARAMS:  bAssertion  Boolean expression.         msg         Fail message.RETURNS: NOTES:   Must define ASSERT = true in any module using this routine.*/function assert( bAssertion, msg ){   if ( ASSERT && !bAssertion ) alert( "ASSERTION FAILED: " + msg )}/*DESCR:   Determines if a variable has been defined.PARAMS:  identifier  The identifier to test.RETURNS: true if the identifier is defined; false otherwise.NOTES:   */function defined( identifier ){   return ( typeof identifier == "undefined" ? false : true )}