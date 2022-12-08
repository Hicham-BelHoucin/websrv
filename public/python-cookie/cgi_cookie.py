import os, cgi

form = cgi.FieldStorage()
name = form.getvalue('name')

# to get the data from fields
email = form.getvalue('email')

def printallcookies():
	if 'HTTP_COOKIE' in os.environ:
		cookies = os.environ['HTTP_COOKIE']
		cookies = cookies.split('; ')

		for cookie in cookies:
			(_name, _value) = cookie.split('=')
			print("<p>" + _name + "=" + _value + "</p>")


def get_cookie(_match):
  # Returns the value from the matching cookie or '' if not defined.
	if 'HTTP_COOKIE' in os.environ:
		cookies = os.environ['HTTP_COOKIE']
		cookies = cookies.split('; ')

		for cookie in cookies:
			(_name, _value) = cookie.split('=')
			if (_match.lower() == _name.lower()):
				return _value
			return('')

if name != None :
	print ("Set-Cookie: name=" + name + "\r\n")
if email != None :
	print ("Set-Cookie: email=" + email + "\r\n")

print ("Content-type:text/html\r\n\r\n")

printallcookies();