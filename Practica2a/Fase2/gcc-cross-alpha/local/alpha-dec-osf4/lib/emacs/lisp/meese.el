;;; meese.el --- protect the impressionable young minds of America

;; This is in the public domain on account of being distributed since
;; 1985 or 1986 without a copyright notice.

;; Maintainer: FSF
;; Keywords: games

;;; Code:

(defun protect-innocence-hook ()
  (let ((dir (file-name-directory buffer-file-name)))
    (if (and (equal buffer-file-name (expand-file-name "sex.6" dir))
	     (file-exists-p buffer-file-name)
	     (not (y-or-n-p "Are you over 18? ")))
	(progn
	  (clear-visited-file-modtime)
	  (setq buffer-file-name (expand-file-name "celibacy.1" dir))
	  (let ((inhibit-read-only t))	; otherwise (erase-buffer) may bomb.
	    (erase-buffer)
	    (insert-file-contents buffer-file-name t))
	  (rename-buffer (file-name-nondirectory buffer-file-name))))))

(add-hook 'find-file-hooks 'protect-innocence-hook)
(provide 'meese)

;;; meese.el ends here
