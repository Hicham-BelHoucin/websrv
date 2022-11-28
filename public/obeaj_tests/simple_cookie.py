import cgi, cgitb
from os import environ
  
# to create instance of FieldStorage 
# class which we can use to work 
# with the submitted form data
form = cgi.FieldStorage()      
name = form.getvalue('name')    
  
# to get the data from fields
email = form.getvalue('email')   
if 'HTTP_COOKIE' in environ:
   for cookie in map(strip, split(environ['HTTP_COOKIE'], ';')):
      (key, value ) = split(cookie, '=');
      if key == "UserID":
         name = value

      if key == "Email":
         email = value
else:
       print ("Set-Cookie:UserID = %s;\r\n" % name)
       print ("Set-Cookie:Email = %s;\r\n" % email)
print ("Content-Type: text/html \r\n\r\n")
print ("<html>")
print ("<head>")
print ("<title>First CGI Program</title>")
print ("</head>")
print ("<body>")
print ("<h2>Hello, %s %s</h2>" 
       % (name, email))
print ("</body>")
print ("</html>")