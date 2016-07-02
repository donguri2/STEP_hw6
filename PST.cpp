#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

double make_number(const string &str,const int index1,const int index2 = 0){
    string ret ="";
    for (int i = index2; i < index1; ++i){
        ret +=str[i];
    }
    return atof(ret.c_str());
}

void read_file(char const *argv,vector<double> &x,vector<double> &y){
	ifstream fin(argv);
	string str;
    int index;
    int i=0;

    if( !fin ){
        cout << "Error: cannot open file(" << argv << ")" << endl;
        exit(1);
    }
    getline(fin,str);
    while(getline(fin,str)){
        index = (int)str.find(",");
        x.push_back(make_number(str,index));
        y.push_back(make_number(str,str.length(),index+1));
        i++;
        }    	
}

double calculate_distance(const double &x1,const double &y1,const double &x2,const double &y2){
    int ret=0;
    ret = pow(x1-x2,2) + pow(y1-y2,2);
    return sqrt(ret);
}

//点indexから近い点を探す
double search_near_vertex(const vector<double> &x,const vector<double> &y,int &next,map<int,bool> &mp){
    double ret=INFINITY;
    double distance;
    int index = next;

    for (int i = 0; i < x.size(); ++i){
        if(i != index){
            distance = calculate_distance(x[index],y[index],x[i],y[i]);
            //printf("distance;%dto%d : %lf\n",index,i,distance );
            //条件は距離が他の辺より短くてまだ繋がっていない
            if(distance <= ret && mp[i] != true){
                ret = distance;
                next = i;
            }
        }
    }
    mp[next] = true;
    return ret;
}

double search_best_way(const vector<double> &x,const vector<double> &y){
    map<int,bool> mp;
    mp[0] = true;
    double distance = 0;
    double dummy_distance = 0;
    int next = 0;
 
    while(dummy_distance != INFINITY){
        distance = dummy_distance;
        cout << next << endl;
        dummy_distance += search_near_vertex(x,y,next,mp);
    }
    distance += calculate_distance(x[next],y[next],x[0],y[0]);
    return distance;
}

int main(int argc, char const *argv[]){
    vector<double> x;
    vector<double> y;
    double distance;

	if(argc != 2){         //ファイルの数調整
		cout << "Please put one file!" << endl;
		exit(-1);
	}

	read_file(argv[1],x,y);
    distance = search_best_way(x,y);
    cout << "distance:" << distance << endl;

	return 0;
}