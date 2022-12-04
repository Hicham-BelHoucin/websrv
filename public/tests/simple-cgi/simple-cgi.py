import cgi, cgitb
from os import environ
  
# to create instance of FieldStorage 
# class which we can use to work 
# with the submitted form data
form = cgi.FieldStorage()      
name = form.getvalue('name')    
email = form.getvalue('email')
# to get the data from fields
print ("Content-Type: text/html \r\n\r\n")
print ("<html>")
print ("<head>")
print ("<title>First CGI Program</title>")
print ("</head>")
print ("<body>")
print ("<h2>Hello, %s %s</h2>" 
       % (name, email))
print ("<h2>Hello, %s </h2>" 
       % (environ))
print ("</body>")
print ("</html>")