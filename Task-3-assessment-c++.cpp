#include <iostream>
#include <unordered_map>
#include <vector>
#include <list>
#include <string>
#include <algorithm> //randomshuffle

typedef std::unordered_map <std::string, std::vector<std::string>> preference_table_type;
typedef std::unordered_map <std::string, std::string> matching_type;

std::tuple<preference_table_type, preference_table_type, matching_type> fundamental_algorithm_new(int t)
    {
    
    //create 2 lists for men and women
    std::vector<std::string> men;
    std::vector<std::string> women;
    std::string s;
    
    for (int i=1; i<=t; i++) {
        
        s = std::to_string(i); //from stackoverflow
        men.push_back("M"+s);
        women.push_back("F"+s);
    }
    
    
    //create empty preference tables called p5 (p1) and p6 (p2)
    
    std::unordered_map <std::string, std::vector<std::string>> p5; //male preference table
    std::unordered_map <std::string, std::vector<std::string>> p6; //female preference table
    
    //male preference table
    
    for (auto i : men)
    {
        std::random_shuffle(women.begin(), women.end());
        p5[i] = women;
    }
    
    //female preference table
    
    for (auto i : women)
    {
        std::random_shuffle(men.begin(), men.end());
        p6[i] = men;
    }
    
    //make copies of original preference tables so can output them 
    std::unordered_map <std::string, std::vector<std::string>> output_p5 {p5};
    std::unordered_map <std::string, std::vector<std::string>> output_p6 {p6};
    
    // all women temporariliy engaged to undesirable man
    //hence initial matchings are:
    std::unordered_map<std::string, std::string> m;
    
    for (const auto& i:women)
    {
        m[i] = "omega";
    }
    
    int k = 0;
    int n = p6.size();
    
    //add omega to end of list of preferences for each woman
    for (auto i : p6){
        p6.at(i.first).push_back("omega");
    }
    
    
    //while not all men have matches
    while (k<n){
        std::string X = men[k];
            while (X!="omega"){
                // X's list of preferences
                std::vector<std::string> preference_list = p5[X];
                
                //get best choice
                std::string x = preference_list[0];
                
                //currnet partner (fiance) of women x is:
                std::string h = m[x];
                
                //find index of current partner
                auto i = std::find(p6[x].begin(), p6[x].end(), h);
                int current_index = std::distance(p6[x].begin(),i);
                
                //find index of new potential partner
                i = std::find(p6[x].begin(), p6[x].end(), X);
                int potential_index = std::distance(p6[x].begin(),i);
                
                //if women preferes new man then engage them
                if (potential_index < current_index)
                {
                    m[x]=X;
                    X = h;
                }
                
                if (X != "omega")
                {
                    p5[X].erase(p5[X].begin());
                }
            }
        k = k+1;
        }
    std::tuple <preference_table_type, preference_table_type, matching_type> out (output_p5, output_p6, m);
    
       
    return out;

}

int main()
{
	int T;
	std::cout << "Please provide number of males and females:" << std::endl;
	std::cin >> T;
	
	std::tuple<preference_table_type, preference_table_type, matching_type>out_out;
	out_out = fundamental_algorithm_new(T);
	
	std::cout << "Male Preference Table" << std::endl;
	// print male preference table
	for (const auto& i : std::get<0>(out_out)) 
	{
    		std::cout << "{" << i.first << ":";
    		for (const auto& j : i.second)
    		{
        		std::cout << j << ",";
    		}
    		std::cout << "}" << std::endl;
	}
	
	//print female preference table
	
	std::cout << "Female Preference Table" << std::endl;
	
	for (const auto& i : std::get<1>(out_out))
	{
    		std::cout << "{" << i.first << ":";
    		for (const auto& j : i.second)
    		{
        		std::cout << j << ",";
    		}
    		std::cout << "}" << std::endl;
	}
	
	std::cout << "Stable Matching" << std::endl;
	
	//print matching
	for (const auto& i : std::get<2>(out_out))
	{
    		std::cout << "(" << i.first << ":" << i.second << ")" << std::endl;
	}
	
	return 0;
} 
        
