import cgi, cgitb              
  
# to create instance of FieldStorage 
# class which we can use to work 
# with the submitted form data
form = cgi.FieldStorage()      
name = form.getvalue('name')    
  
# to get the data from fields
email = form.getvalue('email')   
  
print ("<html>")
print ("<head>")
print ("<title>First CGI Program</title>")
print ("</head>")
print ("<body>")
print ("<h2>Hello, %s %s</h2>" 
       % (name, email))
  
print ("</body>")
print ("</html>")