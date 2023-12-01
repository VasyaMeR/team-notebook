double readNumber() {
    const int BSIZE = 4096;
    static char buffer[BSIZE];
    static char* bptr = buffer + BSIZE;
    auto getChar = []() {
        if (bptr == buffer + BSIZE) {
            memset(buffer, 0, BSIZE);
            cin.read(buffer, BSIZE);
            bptr = buffer;
        }
        return *bptr++;
    };
    char c = getChar(); 
    while (c && (c < '0' || c > '9') && c != '-') 
        c = getChar();
    bool minus = false;
    if (c == '-') minus = true, c = getChar();
    double res = 0;
    
    while (c >= '0' && c <= '9') { 
        res = res * 10 + c - '0'; 
        c = getChar(); 
    }

      if (c == '.') {
        c = getChar();
        double cur = 0.1;
        while (c >= '0' && c <= '9') { 
            res = res + (c - '0') * cur;
            c = getChar();
            cur /= 10.0;
        }
    }
    return minus ? -res : res;
}
