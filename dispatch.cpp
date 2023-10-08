#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<utility>
#include<map>

using namespace std;

void capoverflow(vector<int>&v,map<int,vector<float>>&mp,float diff){
    float sum = 0;
    for(auto a:v){
        sum+=mp[a][0];
    }
    
    for(auto a:v){
        mp[a][0] = mp[a][0]-(mp[a][0]/sum)*diff;
    }
}

void diffadjustment(vector<vector<float>>&v, float regsum){
    
    float sum = 0;
    for(auto a:v){
        sum+=a[0];
    }
    
    float diff = sum-regsum;
    for(auto &a:v){
        a[0] = a[0]-(a[0]/sum)*diff;
    }
}

char regchar(int i){
    if(i==0){
        return 'E';
    }
    if(i==1){
        return 'W';
    }
    if(i==2){
        return 'N';
    }
    if(i==3){
        return 'S';
    }
    return '\0';
}

int main(){
 
    //given data
    int stforecast=12000;
    float r[4];
    r[0]=2800;//east
    r[1]=2000;//west
    r[2]=1500;//north
    r[3]=6500;//south


    float sumreg = r[0]+r[1]+r[2]+r[3];
    float diffreg = sumreg-stforecast;


    float newsum = 0;
    for(int i=0;i<4;i++){
        r[i]=r[i]-(r[i]/sumreg)*diffreg;
        //newsum+=r[i];
    }
    //cout<<newsum<<endl;

    //input data region wise
    vector<vector<vector<float>>>regions(4);
    //region [0]->east ,1->west,2->north,3->south.
    
    ifstream fin;
    fin.open("input.csv");
    vector<string> row; 
    string line, word, temp; 
    int l = 0,es=0,w=0,n=0,st=0;
    while (getline(fin,line)) { 

        row.clear(); 

        istringstream s(line);

        while (getline(s, word, ',')) { 
            //add the individual forecasts to it's regional vector;
            row.push_back(word); 
        }

        string temp2 = row[0];
        //cout<<temp2<<endl;
        if(temp2[0]=='E'){
            es++;
            regions[0].push_back({stof(row[1]),stof(row[2])});
        }
        if(temp2[0]=='W'){
            w++;
            regions[1].push_back({stof(row[1]),stof(row[2])});
        }
        if(temp2[0]=='N'){
            n++;
            regions[2].push_back({stof(row[1]),stof(row[2])});
        }
        if(temp2[0]=='S'){
            st++;
            regions[3].push_back({stof(row[1]),stof(row[2])});
        }
        l++;
        
    } 
    /*cout<<es<<" "<<w<<" "<<n<<" "<<st<<endl;
    cout<<l<<endl;*/

    //manipulating by region
    for(int i=0;i<4;i++){
        diffadjustment(regions[i],r[i]);
    }

        /*
    std::ofstream ofs;
ofs.open("output2.csv", std::ofstream::out | std::ofstream::trunc);
ofs.close();
ofs.open("output1.csv", std::ofstream::out | std::ofstream::trunc);
ofs.close();
*/

    //output after region manipulation, that is after considering constraint 1 and 2
        fstream fout; 
  
    // opens an existing csv file or creates a new file. 
    fout.open("output1.csv", ios::out | ios::app); 
    fout<<"Plant"<<","<<"Forecast"<<","<<"Capacity"<<"\n";
    
    for(int i=0;i<4;i++){
        int ind = 1;
        for(auto val:regions[i]){
            fout<<regchar(i)<<to_string(ind)<<","<<to_string(val[0])<<","<<to_string(val[1])<<"\n";
            ind++;
        }
    }
    
    //adjusting values which became higher than capacity
    int count = 0;
    for(int i = 0;i<4;i++){
      //let's  index vectors on map
      map<int,vector<float>>mp;
      
      vector<int>overind;//indexes where max capacity crossed
      vector<int>current(regions[i].size()); //indexes in check
      for(int j=0;j<current.size();j++){
          current[j]=j;
          mp[j]=regions[i][j];
      }
      
      bool capexceeded = true;
      int k = 0;
      while(capexceeded  && k<15){//k is less than 15 to keep the iterations to 15 and not exceed 15 iterations , we can increase this for better results.
        float diff = 0;
        capexceeded = false;
        int k = 1;
        for(auto it = current.begin();it!=current.end();it++){
            //cout<<mp[(*it)][0]<<" "<<mp[(*it)][1]<<endl;
            if(mp[(*it)][0]>=mp[(*it)][1]){
                capexceeded = true;
                diff+=mp[(*it)][0]-mp[(*it)][1];
                mp[(*it)][0]=mp[(*it)][1];
                
                overind.push_back(*it);
                current.erase(it);
                it--;
            }
        }
        capoverflow(current,mp,diff);
        k++;
      }

      for(int j = 0;j<regions[i].size();j++){
        regions[i][j]=mp[j];//adding all the new vectors where capacity is not overflowed.
      }
      count++;
      cout<<count<<endl;
      
    }
        



    //saving output    
    fstream fout2; 
  
    // opens an existing csv file or creates a new file. 
    fout2.open("output2.csv", ios::out | ios::app); 
    fout2<<"Plant"<<","<<"Forecast"<<","<<"Capacity"<<"\n";
    
    for(int i=0;i<4;i++){
        int ind = 1;
        for(auto val:regions[i]){
            fout2<<regchar(i)<<to_string(ind)<<","<<to_string(val[0])<<","<<to_string(val[1])<<"\n";
            ind++;
        }
    }
    
    
    return 0;
}