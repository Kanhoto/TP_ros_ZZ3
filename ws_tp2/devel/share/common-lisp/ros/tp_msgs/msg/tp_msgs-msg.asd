
(cl:in-package :asdf)

(defsystem "tp_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "Sinus" :depends-on ("_package_Sinus"))
    (:file "_package_Sinus" :depends-on ("_package"))
  ))