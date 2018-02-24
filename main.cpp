#include <iostream>
#include <stdio.h>
#include <cmath>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include <thread>
#include <sstream>
using namespace std;
const double TWO_PI = 6.283185307179586;

bool swapXY = true,
invertX = false,
invertY = false;
double minfps = 15.0;
double maxfps = 30.0;

bool fexit = false;
double steps = 2000.0;

vector<pair<double,double> > buffer;
string frame;
double step = 0.4;

inline void draw(double x, double y, double x1, double y1, double csp=1) {
	double rs = sqrt((x1-x)*(x1-x)+(y1-y)*(y1-y));
	double dx = (x1-x)/rs*step*csp;
	double dy = (y1-y)/rs*step*csp;
	while (((x>x1 && dx<0) || (x<x1 && dx>0)) || ((y>y1 && dy<0) || (y<y1 && dy>0)))
	{
		buffer.push_back({x,y});
		x += dx;
		y += dy;
	}
}

void symb(double x, double y, string s) {
	double p = 30;
	if (s[0]>='a'&&s[0]<='z'){
		p /= 2;char c = s[0];
		s = "";s += c+'A'-'a';
	}
	if (s=="-") {
		draw(x,y+p,x+p,y+p);
	}
	else if (s=="1") {
		draw(x+p,y,x+p,y+p*2);
	}
	else if (s=="2") {
		draw(x,y+p*2,x+p,y+p*2);
		draw(x+p,y+p*2,x+p,y+p);
		draw(x+p,y+p,x,y+p);
		draw(x,y+p,x,y);
		draw(x,y,x+p,y);
	}
	else if (s=="3" || s=="З") {
		draw(x,y+p*2,x+p,y+p*2);
		draw(x+p,y+p*2,x+p,y+p);
		draw(x+p,y+p,x,y+p);
		draw(x+p,y+p,x+p,y);
		draw(x+p,y,x,y);
	}
	else if (s=="8") {
		draw(x,y,x,y+p*2);
		draw(x,y+p*2,x+p,y+p*2);
		draw(x+p,y+p*2,x+p,y);
		draw(x+p,y+p,x,y+p);
		draw(x+p,y,x,y);
	}
	else if (s=="5" || s=="S") {
		draw(x,y,x+p,y);
		draw(x+p,y,x+p,y+p);
		draw(x+p,y+p,x,y+p);
		draw(x,y+p,x,y+p*2);
		draw(x,y+p*2,x+p,y+p*2);
	}
	else if (s=="7") {
		draw(x,y+p*2,x+p,y+p*2);
		draw(x+p,y+p*2,x+p,y);
	}
	else if (s=="9") {
		draw(x,y,x+p,y);
		draw(x+p,y,x+p,y+p);
		draw(x+p,y+p,x,y+p);
		draw(x,y+p,x,y+p*2);
		draw(x,y+p*2,x+p,y+p*2);
		draw(x+p,y+p*2,x+p,y+p);
	}
	else if (s=="А" || s=="A") {
		draw(x,y,x+p/2,y+p*2);
		draw(x+p/2,y+p*2,x+p*0.75,y+p);
		draw(x+p*0.75,y+p,x+7.5,y+p,2);
		draw(x+7.5,y+p,x+p*0.75,y+p,2);
		draw(x+p*0.75,y+p,x+p,y);
	}
	else if (s=="Б" || s=="6" || s=="G") {
		draw(x,y,x,y+p);
		draw(x,y+p,x,y+p*2,2);
		draw(x,y+p*2,x+p,y+p*2,2);
		draw(x+p,y+p*2,x,y+p*2,2);
		draw(x,y+p*2,x,y+p,2);
		draw(x,y+p,x+p,y+p);
		draw(x+p,y+p,x+p,y);
		draw(x+p,y,x,y);
	}
	else if (s=="В" || s=="B") {
		draw(x,y,x,y+p*2);
		draw(x,y+p*2,x+p,y+p*1.5);
		draw(x+p,y+p*1.5,x,y+p);
		draw(x,y+p,x+p,y+p/2);
		draw(x+p,y+p/2,x,y);
	}
	else if (s=="D") {
		draw(x,y,x,y+p*2);
		draw(x,y+p*2,x+p/2,y+p*2);
		draw(x+p/2,y+p*2,x+p,y+p*1.5);
		draw(x+p,y+p*1.5, x+p,y+p/2);
		draw(x+p,y+p/2,x+p/2,y);
		draw(x+p/2,y,x,y);
	}
	else if (s=="Г") {
		draw(x,y,x,y+p*2);
		draw(x,y+p*2,x+p,y+p*2);
	}
	else if (s=="Д") {
		draw(x,y,x,y+p/6);
		draw(x,y+p/6,x+p/6,y+p/6);
		draw(x+p/6,y+p/6,x+p/6,y+p*2);
		draw(x+p/6,y+p*2,x+p*5/6,y+p*2);
		draw(x+p*5/6,y+p*2,x+p*5/6,y+p/6);
		draw(x+p*5/6,y+p/6,x+p/6,y+p/6,2);
		draw(x+p/6,y+p/6,x+p*5/6,y+p/6,2);
		draw(x+p*5/6,y+p/6,x+p,y+p/6);
		draw(x+p,y+p/6,x+p,y);
	}
	else if (s=="Е" || s=="Ё" || s=="E") {
		draw(x,y,x,y+p*2);
		draw(x,y+p*2,x+p,y+p*2);
		draw(x+p,y+p,x,y+p);
		draw(x,y,x+p,y);
	}
	else if (s=="F") {
		draw(x,y,x,y+p*2);
		draw(x,y+p,x+p,y+p);
		draw(x,y+2*p,x+p,y+2*p);
	}
	else if (s=="I") {
		draw(x+p/2,y,x+p/2,y+p*2);
	}
	else if (s=="J") {
		draw(x,y+p/4,x+p/4,y);
		draw(x+p/4,y,x+p,y+p/4);
		draw(x+p,y+p/4,x+p,y+p*2);
		draw(x+p/4,y+p*2,x+p*3/4,y+p*2);
	}
	else if (s=="L") {
		draw(x,y+p*2,x,y);
		draw(x,y,x+p,y);
	}
	else if (s=="N") {
		draw(x,y,x,y+p*2);
		draw(x,y+p*2,x+p,y);
		draw(x+p,y,x+p,y+p*2);
	}
	else if (s=="И") {
		draw(x,y,x,y+p*2,2);
		draw(x,y+p*2,x,y,2);
		draw(x,y,x+p,y+p*2);
		draw(x+p,y+p*2,x+p,y);
	}
	else if (s=="Й") {
		draw(x,y,x,y+p*2);
		draw(x,y,x+p,y+p*2);
		draw(x+p,y+p*2,x+p,y);
		draw(x+p/2,y+70,x+p*5/6,y+70);
	}
	else if (s=="К" || s=="K") {
		draw(x,y,x,y+p*2);
		draw(x,y+p,x+p,y+p*2);
		draw(x,y+p,x+p,y);
	}
	else if (s=="Л") {
		draw(x,y,x+p/2,y+p*2);
		draw(x+p/2,y+p*2,x+p,y);
	}
	else if (s=="М" || s=="M") {
		draw(x,y,x,y+p*2);
		draw(x,y+p*2,x+p/2,y+40);
		draw(x+p/2,y+40,x+p,y+p*2);
		draw(x+p,y+p*2,x+p,y);
	}
	else if (s=="Н" || s=="H") {
		draw(x,y,x,y+p*2);
		draw(x,y+p,x+p,y+p);
		draw(x+p,y+p*2,x+p,y);
	}
	else if (s=="О" || s=="0" || s=="O") {
		draw(x,y,x,y+p*2);
		draw(x,y+p*2,x+p,y+p*2);
		draw(x+p,y+p*2,x+p,y);
		draw(x+p,y,x,y,2);
		draw(x,y,x+p,y,2);
	}
	else if (s=="П") {
		draw(x,y,x,y+p*2);
		draw(x,y+p*2,x+p,y+p*2);
		draw(x+p,y+p*2,x+p,y);
	}
	else if (s=="Р" || s=="P") {
		draw(x,y,x,y+p,2);
		draw(x,y+p,x,y+p*2);
		draw(x,y+p*2,x+p,y+p*2);
		draw(x+p,y+p*2,x+p,y+p);
		draw(x+p,y+p,x,y+p);
		draw(x,y+p,x,y,2);
	}
	else if (s=="С" || s=="C") {
		draw(x+p,y+p*2,x,y+p*2);
		draw(x,y+p*2,x,y);
		draw(x,y,x+p,y);
	}
	else if (s=="Т" || s=="T") {
		draw(x+p/2,y,x+p/2,y+p*2);
		draw(x+p/2,y+p*2,x,y+p*2,2);
		draw(x,y+p*2,x+p/2,y+p*2,2);
		draw(x+p/2,y+p*2,x+p,y+p*2);
	}
	else if (s=="У") {
		draw(x,y,x+p,y+p*2);
		draw(x,y+p*2,x+p/2,y+p);
	}
	else if (s=="Ф") {
		draw(x+p/2,y,x+p/2,y+p*2);
		draw(x+p,y+p*2,x,y+p*2);
		draw(x,y+p*2,x,y+p);
		draw(x,y+p,x+p,y+p);
		draw(x+p,y+p,x+p,y+p*2);
	}
	else if (s=="Х" || s=="X") {
		draw(x,y,x+p,y+p*2);
		draw(x,y+p*2,x+p,y);
	}
	else if (s=="Ц") {
		draw(x,y+p*2,x,y+p/6);
		draw(x,y+p/6,x+p,y+p/6);
		draw(x+p*5/6,y+p*2,x+p*5/6,y+p/6);
		draw(x+p,y+p/6,x+p,y);
	}
	else if (s=="Ч" || s=="4") {
		draw(x,y+p*2,x,y+p);
		draw(x,y+p,x+p,y+p);
		draw(x+p,y+p*2,x+p,y);
	}
	else if (s=="Ы") {
		draw(x,y,x,y+p);
		draw(x,y+p,x,y+p*2,2);
		draw(x,y+p*2,x,y+p,2);
		draw(x,y+p,x+20,y+p);
		draw(x+20,y+p,x+20,y);
		draw(x+20,y,x,y);
		draw(x+p,y,x+p,y+p*2);
	}
	else if (s=="Ь") {
		draw(x,y,x,y+p*2);
		draw(x,y+p,x+p,y+p);
		draw(x+p,y+p,x+p,y);
		draw(x+p,y,x,y);
	}
	else if (s=="Ю") {
		draw(x,y,x,y+p*2);
		draw(x,y+p,x+10,y+p);
		draw(x+10,y,x+10,y+p*2);
		draw(x+10,y+p*2,x+p,y+p*2);
		draw(x+p,y+p*2,x+p,y);
		draw(x+p,y,x+10,y);
	}
	else if (s=="Я") {
		draw(x,y,x+p,y+p);
		draw(x+p,y+p,x,y+p);
		draw(x,y+p,x,y+p*2);
		draw(x,y+p*2,x+p,y+p*2);
		draw(x+p,y+p*2,x+p,y);
	}
	else if (s=="R") {
		draw(x,y,x,y+2*p);
		draw(x,y+2*p,x+p,y+2*p);
		draw(x+p,y+p*2,x+p,y+p);
		draw(x+p,y+p,x,y+p);
		draw(x,y+p,x+p,y);
	}
	else if (s=="+") {
		draw(x,y+p,x+p,y+p);
		draw(x+p/2,y+p/2,x+p/2,y+p*1.5);
	}
	else if (s=="=") {
		draw(x,y+p*0.8,x+p,y+0.8*p);
		draw(x,y+p*1.2,x+p,y+1.2*p);
	}
	else if (s=="*") {
		draw(x,y+p*1.5,x+p,y+p*0.5);
		draw(x,y+p*0.5,x+p,y+p*1.5);
	}
	else if (s=="^") {
		draw(x,y+p*1.5,x+p/2,y+p*2);
		draw(x+p/2,y+p*2,x+p,y+p*1.5);
	}
	else if (s=="/") {
		draw(x+p*0.2,y,x+p*0.8,y+p*2);
	}
	else if (s=="." || s==",") {
		draw(x+p*0.4,y,x+p*0.6, y+p*0.2);
	}
	else if (s=="(") {
		draw(x+0.7*p,y,x+0.3*p,y+p);
		draw(x+0.3*p,y+p,x+0.7*p,y+p*2);
	}
	else if (s==")") {
		draw(x+0.3*p,y,x+0.7*p,y+p);
		draw(x+0.7*p,y+p,x+0.3*p,y+p*2);
	}
}

void writetext(vector<string> s) {
	double y = (s.size()-1)*80;
	double x = 0;
	double xmax = 0, ymax = max(y + 60,300.0);
	buffer.clear();
	for (string i:s) {
		xmax = max(xmax, (double)i.size());
		for (char j:i) {
			string sj; sj += j;
			symb(x,y,sj);
			x += 45;
		}
		x = 0;
		y -= 80;
	}
	xmax = (xmax-1)*45 + 30;
	//swap buffers
	double mx = max(xmax, ymax)/2;
	string framebuffer = "";
	for (int i = 0;i<buffer.size();++i) {
		x = buffer[i].first;
		y = buffer[i].second;
		x /= mx; y /= mx;
		x--; y--;
		if (invertY) y = -y;
		if (invertX) x = -x;
		if (swapXY) swap(x,y);
		short sx = x*32767;
		short sy = y*32767;
		framebuffer += (unsigned char)(sx>>8);
		framebuffer += (unsigned char)sx;
		framebuffer += (unsigned char)(sy>>8);
		framebuffer += (unsigned char)sy;
	}
	double fps = 4*192000.0 / framebuffer.size();
	if (fps<minfps) fps *= minfps/fps;
	if (fps>maxfps) fps *= maxfps/fps;
	swap(frame, framebuffer);
}


void sound() {
	string _1 = "aplay -r 192000 -c 2 -f S16_BE -t raw ";
	FILE *p = popen(_1.c_str(),"w");
	while (!fexit) {
		int sz = frame.size();
		if (!sz) {
			frame = string(192, (unsigned char)127);
		}
		double time = clock();
		fwrite(frame.c_str(), 1, sz, p);
		double diff = double(sz)/4/192000 - ((double)clock()-time)/1000.0;
		usleep(max(diff*999999,0.0));
	}
	pclose(p);
	
}

void genwave(int f) {
	int freq = 440.0*440.0/f;
	int count = 192000/freq*freq;
	string framebuffer;
	for (int i = 0;i<count;++i) {
		short sx = sin(i*TWO_PI/freq)*32767;
		short sy = sin(i*TWO_PI/freq)*32767;
		framebuffer += (unsigned char)(sx>>8);
		framebuffer += (unsigned char)sx;
		framebuffer += (unsigned char)(sy>>8);
		framebuffer += (unsigned char)sy;
	}
	swap(frame, framebuffer);
}

string repl(string s) {
	for (int i = 0;i<s.size();++i) {
		if (s[i]=='^') {
			s = s.replace(i,1,"**");
		}
		if (s[i]=='/') {
			s = s.replace(i,1,"*1.0/");
			i += 4;
		}
	}
	return s;
}

bool isnumb(string str)
{
	return !isnan(atof(str.c_str()));
}
	
int main() {
	thread thrSound(sound);
	thrSound.detach();
	vector<string> text;
	text.push_back("");
	int mode = 0;//calc, graph
	bool calculated = 0;
	string lastout;
	double range = 3.0;
	system("/bin/stty raw");
	while (true) {
		if (mode==0) {
			char ch = getchar();
			if (calculated) {
				calculated = 0;
				if (ch!=127 || text[0]=="ERROR") text[0] = "";
				if (ch=='+' || ch=='-' || ch=='^' || ch=='*' || ch=='/') text[0] += lastout;
			}
			//27 - esc
			//13 - enter
			//127 - backspace
			if (ch==27) break;
			else if (ch==127) {
				if (text[0] != "") text[0].pop_back();
			}
			else if (ch==13) {
				int j;
				for (j = 0;j<text[0].size();++j) {
					if (text[0][j]=='x') break;
				}
				if (j==text[0].size()) {
					string cmd = "python eval.py \"int(("+repl(text[0])+")*10**8)*1.0/10**8\"";
					FILE *p = popen(cmd.c_str(),"r");
					char buf[1024];
					size_t szout = fread(buf, 1, 1024, p);
					buf[szout] = 0;
					string out = buf;
					out = out.substr(0,out.size()-1);
					pclose(p);
					if (out.size()>=2) {
						if (out[out.size()-1]=='0' && out[out.size()-2]=='.') out = out.substr(0,out.size()-2);
					}
					if (out=="ERROR") {
						lastout = "";
						text[0] = out;
					}
					else {
						lastout = out; 
						text[0] += "=" + out;
					}
					calculated = 1;
				}
				else {
					range = 3.0;
					mode = 1;
				}
			}
			else if (ch=='c') {
				text[0] = "";
			}
			else text[0] += ch;
			writetext(text);
		}
		else if (mode==1) {
			string framebuffer;
			string cmd = "python eval2.py "+to_string(range)+" "+to_string(steps)+" \""+repl(text[0])+"\"";
			FILE *p = popen(cmd.c_str(),"r");
			char buf[1024*1024];
			size_t szout = fread(buf, 1, 1024*1024, p);
			buf[szout] = 0;
			string out = buf;
			out = out.substr(0,out.size()-1);
			pclose(p);
			int cur = 0;
			for (double i = -range;i<=range;i += range/steps*2) {
				int j;
				for (j = 1;cur+j<out.size();++j) {
					if (out[cur+j]==';') break;
				}
				string curout = out.substr(cur,j);
				cur += j+1;
				if (curout!="ERROR") {
					double y = atof(curout.c_str())/range;
					double x = i/range;
					if (y>=-1 && y<=1) {
						short sx = x*32767;
						short sy = y*32767;
						if (swapXY) {
							framebuffer += (unsigned char)(sy>>8);
							framebuffer += (unsigned char)sy;
						}
						framebuffer += (unsigned char)(sx>>8);
						framebuffer += (unsigned char)sx;
						if (!swapXY) {
							framebuffer += (unsigned char)(sy>>8);
							framebuffer += (unsigned char)sy;
						}
					}
				}
			}
			for (double i = 0;i<steps/10;++i) {
				short sx = 0;
				short sy = (i/(steps/10)*2-1)*32767;
				framebuffer += (unsigned char)(sx>>8);
				framebuffer += (unsigned char)sx;
				framebuffer += (unsigned char)(sy>>8);
				framebuffer += (unsigned char)sy;
			}
			for (double i = 0;i<steps/10;++i) {
				short sy = 0;
				short sx = (i/(steps/10)*2-1)*32767;
				framebuffer += (unsigned char)(sx>>8);
				framebuffer += (unsigned char)sx;
				framebuffer += (unsigned char)(sy>>8);
				framebuffer += (unsigned char)sy;
			}
			swap(frame, framebuffer);
			char ch = getchar();
			if (ch=='+') range /= 2;
			else if (ch=='-') range *= 2;
			else {
				writetext(text);
				mode = 0;
			}
		}
		usleep(5000);
	}
	system("/bin/stty cooked");
	fexit = 1;
	return 0;
}