;; ======================================================================
;; Ladebug functions
;;
;; Tim Lucia   (lucia@zko.dec.com) 30-Oct-95
;; Modified to work with 19.27 release of GUD and with the ladebug debugger
;; release with Digital UNIX V4.0.  The name was changed from decladebug to
;; just ladebug.
;;
;; Tim Bingham (tjb@zko.dec.com) 28-December-1993
;;
;; Based on a version by Dirk Grunwald (grunwald@foobar.cs.colorado.edu)
;;
;; This version makes use of the -emacs option to Ladebug which causes
;; file/line number markers to be output. These markers have the same syntax
;; as those of gdb and so we inherit gud-gdb-marker-filter instead of defining
;; our own gud-ladebug-marker-filter. Similarly we inherit gud-gdb-find-file
;; rather than define gud-ladebug-find-file.
;;
;; These functions require version 2.0.12 or later of Ladebug
;;

;; We are built in terms of the Grand Unified Debugger
(require 'gud)

;; History of argument lists passed to Ladebug
(defvar gud-ladebug-history nil)

;; ladebug activation name -- changed from decladebug to ladebug
;; in Digital UNIX V4.0.
(defvar gud-ladebug-ladebug-name nil)
(setq gud-ladebug-ladebug-name
      (cond ((file-readable-p "/usr/bin/ladebug") "ladebug ")
	    (t "decladebug ")))


;;;####autoload
(defun ladebug (command-line)
  "Run ladebug on program FILE in buffer *gud-FILE*.
The directory containing FILE becomes the initial working directory
and source-file directory for your debugger."
  (interactive
   (list (read-from-minibuffer "Run ladebug (like this): "
			       (if (consp gud-ladebug-history)
				   (car gud-ladebug-history)
				 gud-ladebug-ladebug-name)
			       nil nil
			       '(gud-ladebug-history . 1))))

  (if (fboundp 'gud-overload-functions)
      (progn (defun gud-ladebug-massage-args (&optional file args)
	       (cons "-emacs" (cons file args)))

	     (gud-overload-functions '((gud-massage-args  . gud-ladebug-massage-args)
				       (gud-marker-filter . gud-gdb-marker-filter)
				       (gud-find-file     . gud-gdb-find-file)))
	     (gud-common-init command-line))
    
    (progn 
      (defun gud-ladebug-massage-args (file args)
	(cons "-emacs" args))

      (gud-common-init command-line 'gud-ladebug-massage-args
		       'gud-gdb-marker-filter 'gud-gdb-find-file)))
  
  (gud-def gud-break  "stop at \"%f\":%l" "\C-b" "Set breakpoint at current line of current buffer.")
  (gud-def gud-step   "step"       "\C-s" "Step one line (into functions).")
  (gud-def gud-stepi  "stepi"      "\C-i" "Step one instruction.")
  (gud-def gud-next   "next"       "\C-n" "Step one line (over functions).")
  (gud-def gud-cont   "cont"	   "\C-c" "Continue.")
  (gud-def gud-cont   "return"	   "\C-r" "Return from current function.")
  (gud-def gud-up     "up %p"	   "<"    "Up (numeric arg) stack frames.")
  (gud-def gud-down   "down %p"	   ">"    "Down (numeric arg) stack frames.")
  (gud-def gud-print  "print %e"   "\C-p" "Evaluate expression at point.")

  (setq comint-prompt-regexp  "^[^)]*ladebug) *")

  (run-hooks 'ladebug-mode-hook)

  )

(fset 'decladebug 'ladebug)

;;; ladebug.el ends here
