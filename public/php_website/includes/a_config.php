<?php
	switch ($_SERVER["SCRIPT_NAME"]) {
		case "/php_website/about.php":
			$CURRENT_PAGE = "About";
			$PAGE_TITLE = "About Us";
			break;
		case "/php_website/contact.php":
			$CURRENT_PAGE = "Contact";
			$PAGE_TITLE = "Contact Us";
			break;
		default:
			$CURRENT_PAGE = "Index";
			$PAGE_TITLE = "Welcome to my homepage!";
	}
?>