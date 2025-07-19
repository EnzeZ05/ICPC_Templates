int timeToInt(string s) {
    int hh = stoi(s.substr(0, 2));
    int mm = stoi(s.substr(3));
    return hh * 60 + mm;
}

string intToTime(int x) {
    int hh = x / 60;
    int mm = x % 60;
    string s;

    s += '0' + hh / 10;
    s += '0' + hh % 10;
    s += ':';
    s += '0' + mm / 10;
    s += '0' + mm % 10;

    return s;
}