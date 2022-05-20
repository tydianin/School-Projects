function isStrongPassword(p) {
	i = 0;
	cap = false;
	capCheck = 0;
	
	if (p.length < 8) {
		return false;
	}
	else if (p.indexOf("password") != -1) {
		return false;
	}
	else while (cap == false) {
		capCheck = p.charCodeAt(i);
		if (capCheck >= 65 && capCheck <=90) {
			cap = true;
		}
		else {
			i++;
		}
	}
	return cap;
}