;;; rlogin.el --- remote login interface

;; Author: Noah Friedman
;; Maintainer: Noah Friedman <friedman@prep.ai.mit.edu>
;; Keywords: unix, comm

;; Copyright (C) 1992, 1993, 1994 Free Software Foundation, Inc.
;;
;; This program is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 2, or (at your option)
;; any later version.
;;
;; This program is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.
;;
;; You should have received a copy of the GNU General Public License
;; along with this program; if not, write to: The Free Software Foundation,
;; Inc.; 675 Massachusetts Avenue.; Cambridge, MA 02139, USA.

;;; Commentary:

;; Support for remote logins using `rlogin'.
;; $Id: rlogin.el,v 1.18 1994/06/16 08:09:34 friedman Exp $

;; If you wish for rlogin mode to prompt you in the minibuffer for
;; passwords when a password prompt appears, just enter m-x send-invisible
;; and type in your line, or add `comint-watch-for-password-prompt' to
;; `comint-output-filter-functions'.

;;; Code:

(require 'comint)
(require 'shell)

;;;###autoload
(defvar rlogin-program "rlogin"
  "*Name of program to invoke rlogin")

;;;###autoload
(defvar rlogin-explicit-args nil
  "*List of arguments to pass to rlogin on the command line.")

;;;###autoload
(defvar rlogin-mode-hook nil
  "*Hooks to run after setting current buffer to rlogin-mode.")

;;;###autoload
(defvar rlogin-process-connection-type nil
  "*If non-`nil', use a pty for the local rlogin process.  
If `nil', use a pipe (if pipes are supported on the local system).  

Generally it is better not to waste ptys on systems which have a static
number of them.  On the other hand, some implementations of `rlogin' assume
a pty is being used, and errors will result from using a pipe instead.")

;;;###autoload
(defvar rlogin-initially-track-cwd t
  "*If non-`nil', do remote directory tracking via ange-ftp right away.
If `nil', you can still enable directory tracking by doing 
`M-x dirtrack-toggle'.")

;; Initialize rlogin mode map.
(defvar rlogin-mode-map '())
(cond ((not rlogin-mode-map)
       (setq rlogin-mode-map (cons 'keymap shell-mode-map)) 
       (define-key rlogin-mode-map "\C-c\C-c" 'rlogin-send-Ctrl-C)
       (define-key rlogin-mode-map "\C-c\C-d" 'rlogin-send-Ctrl-D)
       (define-key rlogin-mode-map "\C-c\C-z" 'rlogin-send-Ctrl-Z)
       (define-key rlogin-mode-map "\C-c\C-\\" 'rlogin-send-Ctrl-backslash)
       (define-key rlogin-mode-map "\C-d" 'rlogin-delchar-or-send-Ctrl-D)))

;;;###autoload
(defun rlogin (input-args &optional prefix)
  "Open a network login connection to HOST via the `rlogin' program.
Input is sent line-at-a-time to the remote connection.

Communication with the remote host is recorded in a buffer *rlogin-HOST*,
where HOST is the first word in the string ARGS.  If a prefix argument is
given and the buffer *rlogin-HOST* already exists, a new buffer with a
different connection will be made.

The variable `rlogin-program' contains the name of the actual program to
run.  It can be a relative or absolute path. 

The variable `rlogin-explicit-args' is a list of arguments to give to
the rlogin when starting.  They are added after any arguments given in ARGS."
  (interactive (list (read-from-minibuffer "rlogin arguments (hostname first): ")
                     current-prefix-arg))
  (let* ((process-connection-type rlogin-process-connection-type)
         (buffer-name (format "*rlogin-%s*" input-args))
         args
	 proc
         (old-match-data (match-data)))
    (while (string-match "[ \t]*\\([^ \t]+\\)$" input-args)
      (setq args 
            (cons (substring input-args (match-beginning 1) (match-end 1))
                  args)
            input-args (substring input-args 0 (match-beginning 0))))
    (store-match-data old-match-data)
    (setq buffer-name (format "*rlogin-%s*" (car args))
          args (append args rlogin-explicit-args))
    (and prefix (setq buffer-name 
                      (buffer-name (generate-new-buffer buffer-name))))
    (switch-to-buffer buffer-name)
    (or (comint-check-proc buffer-name)
        (progn
          (comint-mode)
          (comint-exec (current-buffer) buffer-name rlogin-program nil args)
          (setq proc (get-process buffer-name))
          ;; Set process-mark to point-max in case there is text in the
          ;; buffer from a previous exited process.
          (set-marker (process-mark proc) (point-max))
          (rlogin-mode)
          ;; Set the prefix for filename completion and directory tracking
          ;; to find the remote machine's files by ftp.
          (setq comint-file-name-prefix (concat "/" (car args) ":"))
          (and rlogin-initially-track-cwd
               ;; Presume the user will start in his remote home directory.
               ;; If this is wrong, M-x dirs will fix it.
               (cd-absolute (concat "/" (car args) ":~/")))))))

(defun rlogin-mode ()
  "Set major-mode for rlogin sessions. 
If `rlogin-mode-hook' is set, run it."
  (interactive)
  (kill-all-local-variables)
  (shell-mode)
  (setq major-mode 'rlogin-mode)
  (setq mode-name "rlogin")
  (use-local-map rlogin-mode-map)
  (setq shell-dirtrackp rlogin-initially-track-cwd)
  (make-local-variable 'comint-file-name-prefix)
  (run-hooks 'rlogin-mode-hook))


(defun rlogin-send-Ctrl-C ()
  (interactive)
  (send-string nil "\C-c"))

(defun rlogin-send-Ctrl-D ()
  (interactive)
  (send-string nil "\C-d"))

(defun rlogin-send-Ctrl-Z ()
  (interactive)
  (send-string nil "\C-z"))

(defun rlogin-send-Ctrl-backslash ()
  (interactive)
  (send-string nil "\C-\\"))

(defun rlogin-delchar-or-send-Ctrl-D (arg)
  "\
Delete ARG characters forward, or send a C-d to process if at end of buffer."  
  (interactive "p") 
  (if (eobp)
      (rlogin-send-Ctrl-D)
    (delete-char arg)))

;;; rlogin.el ends here
