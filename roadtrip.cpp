#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <cctype>
#include <sstream>
#include <algorithm>
#include <stdio.h>   
#include <stdlib.h>

using namespace std;

struct cityType
{
    string name;
    vector<cityType *> linkCityArray; // array of pointers
    vector<int> linkWeightArray;
    bool isValid;
    int distance;
    cityType * prev;
};

struct tripType
{
    cityType *cityOne;
    cityType *cityTwo;
};

vector<cityType *> shortestPath(cityType * startCity, cityType * endCity, vector<cityType *> arrayCities)
{
    vector<int> q;
    for (int i = 0; i < arrayCities.size(); i++)
    {
        arrayCities[i]->distance=numeric_limits<int>::max();
        if (arrayCities[i]->isValid==true)
        {
            q.push_back(i);
        }
    }
    
    startCity->distance=0;
    cityType * u;
    int minDistance = numeric_limits<int>::max();
    int currentAt = -1;
    int currenti = -1;
    while (q.size()!=0)
    {
        /**
        cout << "q= " << q.size() << "items [";
        for (int i = 0; i < q.size(); i++)
        {
            cout << arrayCities[q[i]]->name << ":" << arrayCities[q[i]]->distance <<", ";   
        } 
        cout << "]"<< endl;
        **/

        int minDistance = numeric_limits<int>::max();   
        for (int i = 0; i < q.size(); i++)
        {
            if (arrayCities[q[i]]->distance < minDistance)
            {
                minDistance=arrayCities[q[i]]->distance;
                currentAt = q[i];
                currenti = i;
            }
        }

        if (minDistance == numeric_limits<int>::max())
        {
            //no more paths.
            break;
        }
        u = arrayCities[currentAt];
        //cout << "removing city: " << u->name  << endl;
        q.erase(q.begin()+currenti);
        /**
        //cout << "q after erasing = " << q.size() << "items [";
        for (int i = 0; i < q.size(); i++)
        {
            cout << arrayCities[q[i]]->name << ":" << arrayCities[q[i]]->distance <<", ";   
        } 
        cout << "]"<< endl;
        **/
        
        //cout << endl;
        for (int i = 0; i < u->linkCityArray.size(); i++)
        {
            int newDistance = u->distance + u->linkWeightArray[i];
            if (newDistance < u->linkCityArray[i]->distance)
            {
                u->linkCityArray[i]->distance = newDistance;
                u->linkCityArray[i]->prev=u;
            }
            //cout << "              (" <<u->linkCityArray[i]->name <<" dist:"<< u->linkCityArray[i]->distance << " prev:" << u->linkCityArray[i]->prev-> name<< " )"  << endl;
        }
    }

    vector<cityType *> pat;
    pat.insert(pat.begin(), endCity);
    cityType * v;
    v = endCity;
    //cout <<"v = " <<v->name<<endl;
    
    while (v!=startCity)
    {
        
    
        pat.insert(pat.begin(), v->prev);
        v=v->prev;
        //cout <<"v = " <<v->name<<endl;

    }
    //cout <<"herere3" <<endl;
    return pat;
}
int main(int argc, char* argv[])
{
     //extract filename and strip leading ./ or / from filename
    string file_to_read = static_cast <string> (argv[1]);
    string inputfile = file_to_read.substr(6,file_to_read.length()-6);
    if (inputfile.substr(0,2)=="./")
    {   inputfile.erase(0,2);}
    else if (inputfile.substr(0,1)=="/")
    {   inputfile.erase(0,1);}

    //cout << "inputfile: " << inputfile <<endl;
    
    vector<cityType *> arrayCities;
    vector<tripType *> arrayTrips;
    cityType constNone;
    constNone.name = "-";
    
    // read file & terminate if not exist
    ifstream file1(inputfile);
    if (!file1){ return 1;}

    //else if file exists
    string line1;
     
    while(getline(file1, line1)) 
    {
        if (line1 == "" || line1.substr(0,1)=="#")
        {
            //ignore line
        }
        else
        {
            //continue: extract content of notice on eachline             
            string word1 = line1.substr(0,line1.find_first_of('\t'));
            line1.erase(0,line1.find_first_of('\t')+1);
            string word2 = line1.substr(0,line1.find_first_of('\t'));
            line1.erase(0,line1.find_first_of('\t')+1);
            string word3 = line1;

            if (word1 != "trip")
            {
                int weight = atoi(word3.c_str());
                int citi1found = -1;
                int citi2found = -1;
                for (int i = 0; i < arrayCities.size(); i++)
                {
                    if (arrayCities[i]->name == word1)
                    {
                        citi1found = i;
                    }
                    if (arrayCities[i]->name == word2)
                    {
                        citi2found = i;
                    }
                }
                if (citi1found==-1)
                {
                    cityType * cityX;
                    cityX = new cityType();
                    cityX->name=word1;
                    cityX->isValid=true;
                    cityX->prev=&constNone;

                    citi1found = arrayCities.size();
                    arrayCities.push_back(cityX);
                }
                if (citi2found==-1)
                {
                    cityType * cityY;
                    cityY = new cityType();
                    cityY->name=word2;
                    cityY->isValid=true;
                    cityY->prev=&constNone;

                    citi2found = arrayCities.size();
                    arrayCities.push_back(cityY);
                }
                //cout << "name: " << word1 << endl;

                arrayCities[citi1found]->linkCityArray.push_back(arrayCities[citi2found]);
                arrayCities[citi1found]->linkWeightArray.push_back(weight);

                arrayCities[citi2found]->linkCityArray.push_back(arrayCities[citi1found]);
                arrayCities[citi2found]->linkWeightArray.push_back(weight);
                
            }
            else
            {
                int citi1found = -1;
                int citi2found = -1;
                for (int i = 0; i < arrayCities.size(); i++)
                {
                    if (arrayCities[i]->name == word2)
                    {
                        citi1found = i;
                    }
                    if (arrayCities[i]->name == word3)
                    {
                        citi2found = i;
                    }
                }
                tripType * tripX;
                tripX = new tripType;
                tripX->cityOne = arrayCities[citi1found];
                tripX->cityTwo = arrayCities[citi2found];
                arrayTrips.push_back(tripX);
            }
        }

    }
    
    
    //cout << "here" << endl<<endl;

    /**  
    for (int i = 0; i < arrayTrips.size(); i++)
    {
        cout << "trip " << arrayTrips[i]->cityOne->name<< " " << arrayTrips[i]->cityTwo->name << endl;
    }
    cout   << endl;**/





    vector<cityType *> path;
    for (int i = 0; i < arrayTrips.size(); i++)
    {

        /**
        cout << "=============" << endl;
        for (int q = 0; q < arrayCities.size(); q++)
        {
            cout << arrayCities[q]->name<< ": isValid=" << arrayCities[q]->isValid<< " [ ";
            for (int r= 0; r < arrayCities[q]->linkCityArray.size(); r++)
            {
                cout << "("<< arrayCities[q]->linkCityArray[r]->name << ":"<< arrayCities[q]->linkWeightArray[r]<< "),";
            }
            cout<< " ] " << endl;
        }
        cout << "=============" << endl;
        **/

        //cout << "here1" <<endl;
        path = shortestPath(arrayTrips[i]->cityOne, arrayTrips[i]->cityTwo, arrayCities);
        //cout << endl;
        for (int j = 0; j < path.size(); j++)
        {
            //cout << "here1" << endl;
            cout << path[j]->name << endl;
            if (path[j]->name != arrayTrips[i]->cityOne->name && path[j]->name != arrayTrips[i]->cityTwo->name )
            {
                path[j]->isValid=false;
                path[j]->linkCityArray.clear();   
                path[j]->linkWeightArray.clear();   
      
            

                ///**
                for (int k = 0; k < arrayCities.size(); k++)
                {
                    for (int l = 0; l < arrayCities[k]->linkCityArray.size(); l++)
                    {
                        if (arrayCities[k]->linkCityArray[l]->name == path[j]->name)
                        {
                            arrayCities[k]->linkCityArray.erase(arrayCities[k]->linkCityArray.begin() + l);
                            arrayCities[k]->linkWeightArray.erase(arrayCities[k]->linkWeightArray.begin() + l);
                        }
                    }
                }      
                //**/ 

            }
            
        }



        /**
        cout << "=============" << endl;
        for (int q = 0; q < arrayCities.size(); q++)
        {
            cout << arrayCities[q]->name<< ": isValid=" << arrayCities[q]->isValid<< " [ ";
            for (int r= 0; r < arrayCities[q]->linkCityArray.size(); r++)
            {
                cout << "("<< arrayCities[q]->linkCityArray[r]->name << ":"<< arrayCities[q]->linkWeightArray[r]<< "),";
            }
            cout<< " ] " << endl;
        }
        cout << "=============" << endl;
        **/

        //cout <<"here"<<endl<<endl<<endl<<endl<<endl;

        //cout << "here2" << endl;
        path = shortestPath(arrayTrips[i]->cityTwo, arrayTrips[i]->cityOne, arrayCities);
        //cout << endl;





        //cout << "here2"<<endl;
        for (int j = 0; j < path.size(); j++)
        {
            //cout << "here1" << endl;
            cout << path[j]->name << endl;
            if (path[j]->name != arrayTrips[i]->cityOne->name && path[j]->name != arrayTrips[i]->cityTwo->name )
            {
                path[j]->isValid=false;
                path[j]->linkCityArray.clear();   
                path[j]->linkWeightArray.clear();   
      
            

                ///**
                for (int k = 0; k < arrayCities.size(); k++)
                {
                    for (int l = 0; l < arrayCities[k]->linkCityArray.size(); l++)
                    {
                        if (arrayCities[k]->linkCityArray[l]->name == path[j]->name)
                        {
                            arrayCities[k]->linkCityArray.erase(arrayCities[k]->linkCityArray.begin() + l);
                            arrayCities[k]->linkWeightArray.erase(arrayCities[k]->linkWeightArray.begin() + l);
                        }
                    }
                }      
                //**/ 

            }
        }

        
        //cout <<  endl<<  endl<<  endl;
    }

}


