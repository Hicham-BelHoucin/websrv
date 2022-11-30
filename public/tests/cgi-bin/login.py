#!/usr/bin/python

import cgi

def header(title):
    print ("Content-Type: text/html \r\n\r\n")
    print ("<HTML><HEAD><TITLE>%s</TITLE></HEAD><BODY>" % (title))

def footer():
    print ("</BODY></HTML>")

form = cgi.FieldStorage()
password = "python"

if not form:
    header("Login Response")
elif form.has_key("login") and form["login"].value != "" and form.has_key("password") and form["password"].value == password:
    header("Connected ...")
    print ("<center><hr><H3>Welcome back," , form["login"].value, ".</H3><hr></center>")
    print (r"""<form><input type="hidden" name="session" value="%s"></form>""" % (form["login"].value))
    print ("<H3><a href=browse.html>Click here to start browsing</a></H3>")

else:
    header("No success!")
    print ("<H3>Please go back and enter a valid login.</H3>")

footer()