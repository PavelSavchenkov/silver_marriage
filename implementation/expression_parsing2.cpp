enum {NUM, NOT, OR, AND, BR1, BR2};

bool isOperation(int t) {
	t = abs(t);
	return t == NOT || t == OR || t == AND;
}
 
bool isUnary(int t) {
	return t == NOT;
}

int priority(int t) {
	if (t < 0) //unary
		return 4;
	if (t == NOT)
		return 3;
	if (t == AND)
		return 2;
	if (t == OR)
		return 1;
	return -1;
}
 
vi st, op;
	
void processOp(int t) {
	if (t < 0) {
		int x = st.back();
		st.pop_back();
		t = -t;
		if (t == NOT)
			st.push_back(1 - x); 
	} else {
		int y = st.back();
		st.pop_back();
		int x = st.back();
		st.pop_back();
		
		switch (t) {
			case AND:	st.push_back(x & y); break;
			case OR:	st.push_back(x | y); break; 
		}
	}
	
	op.pop_back();
}
		 
vector<pair<int, char> > elem;
int reg[MAXN];

int calc() {
	bool may_unary = true;
	
	for (int i = 0; i < elem.size(); i++) {
		
		if (elem[i].X == BR1) {
			
			op.push_back(BR1);
			may_unary = true;
			
		} else if (elem[i].X == BR2) {
			
			while (op.back() != BR1)
				processOp(op.back());
			op.pop_back();
			may_unary = false;
			
		} else if (isOperation(elem[i].X)) {
			
			int t = elem[i].X;
			if (may_unary && isUnary(t)) 
				t = -t;
			while (!op.empty() && (
				(t >= 0 && priority(op.back()) >= priority(t)) ||
				(t < 0 && priority(op.back()) > priority(t))))
				processOp(op.back());
			op.push_back(t);
			may_unary = true;
			
		} else {
			
			st.push_back(reg[elem[i].Y]);							
			may_unary = false;
			
		}
	}
	
	while (!op.empty()) 
		processOp(op.back());
	return st.back();
}				 

void parse(string s) {
	int n = s.size();
	forn(i, 10)
		s += ' ';
	//cerr << s << endl;
			
	for (int i = 0; i < n; ) {
		if (s[i] == ' ') {
			i++;
			continue;
		}
		
		if (s.substr(i, 3) == "NOT") {
			elem.pb(mp(NOT, 0));
			i += 3;
		} else if (s.substr(i, 3) == "AND") {
			elem.pb(mp(AND, 0));
			i += 3;
		} else if (s.substr(i, 2) == "OR") {
			elem.pb(mp(OR, 0));
			i += 2;
		} else if (s.substr(i, 5) == "FALSE") {
			elem.pb(mp(NUM, 0));
			i += 5;
		} else if (s.substr(i, 4) == "TRUE") {
			elem.pb(mp(NUM, 1));
			i += 4;
		} else if (s[i] == '(') {
			elem.pb(mp(BR1, 0));
			i++;
		} else if (s[i] == ')') {
			elem.pb(mp(BR2, 0));
			i++;
		} else {
			elem.pb(mp(NUM, s[i]));
			i++;	
		}	
	}
}