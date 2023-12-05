#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>

using namespace std;

void Rule_R7(vector<string> &input1, vector<vector<string>> &list_of_states, vector<vector<string>> &output){
    regex b("(case)[ ]*\\([ ]*[a-zA-Z0-9_]*(s|S)(tate)[a-zA-Z0-9_]*[ ]*\\)[ ]*[begin]*( -> )[0-9]+");
    int count_case = 0;
    vector<string> v;
    //int i = 0;
    for(auto it1 = input1.begin(); it1 != input1.end(); it1++){
        string s1 = *it1;
        if(regex_match(s1, b)){
            count_case++;
            //cout << s1 << endl;
        }
        if(count_case > 0){
            regex b1("[a-zA-Z0-9_]+[ ]*[<]*[=]+[ ]*[0-9]+(')[a-z]+[01_]*[x_]+[;]*");
            if(regex_search(s1, b1)){
                v.push_back(s1);
                /*int pos1 = s1.find("=");
                string s2 = s1.substr(0, pos1);
                while(s2[0] == ' '){
                    s2.erase(0, 1);
                }
                int len1 = s2.length();
                while(s2[len1 - 1] == ' '){
                    s2.erase(len1 - 1, 1);
                    len1 = s2.length();
                }
                if(find(list_of_states[i].begin(), list_of_states[i].end(), s2) != list_of_states[i].end()){
                    v.push_back(s1);
                }*/
            }
        }
        if(s1.find("endcase") != string::npos && count_case > 0){
            count_case--;
            output.push_back(v);
            v.clear();
            //i++;
        }
    }
}


vector<vector<string>> Rule_R6(vector<vector<string>> &list_of_states, vector<vector<vector<int>>> &transition_of_states){
    vector<vector<string>> output;
    for(int k = 0; k<transition_of_states.size(); k++){
        int N = transition_of_states[k].size();
        vector<string> out;
        vector<vector<int>> graph = transition_of_states[k];
        vector<vector<int>> reach(N, vector<int>(N, 1));
        for(int i = 0; i<N; i++){
            for(int j = 0; j<N; j++){
                if(i!=j){
                    reach[i][j] = graph[i][j];
                }
            }
        }
        for(int k = 0; k<N; k++){
            for(int i = 0; i<N; i++){
                for(int j = 0; j<N; j++){
                    reach[i][j] = reach[i][j] || (reach[i][k] && reach[k][j]);
                }
            }
        }
        for(int l = 0; l<reach[0].size(); l++){
            if(reach[0][l] != 1){
                out.push_back(list_of_states[k][l]);
            }
        }
        output.push_back(out);
    }
    return output;
}

void Rule_R5(vector<vector<vector<int>>> &transition_of_states, vector<vector<string>> &list_of_states, vector<int> &position){
    int m = 0;
    for(int i = 0; i<transition_of_states.size(); i++){
        vector<string> list;
        //vector<string> ones;
        int count_max = transition_of_states[i].size();
        for(int j = 0; j<transition_of_states[i].size(); j++){
            int count = 0;
            for(int k = 0; k<transition_of_states[i].size(); k++){
                if(transition_of_states[i][j][k] == 1){
                    count++;
                }
            }
            if(count <= count_max){
                count_max = count;
            }
            //cout << count_max << " : " << count << endl; 
        }
        //cout << endl;
        for(int j = 0; j<transition_of_states[i].size(); j++){
            int count= 0;
            for(int k = 0; k<transition_of_states[i].size(); k++){
                if(transition_of_states[i][j][k] == 1){
                    count++;
                }
            }
            if(count == count_max){
                //cout << list_of_states[i][j] << " ";
                list.push_back(list_of_states[i][j]);
            }
        }
        cout << "FSM at position : " << position[m] << endl;
        cout << "Initial state is : " << list_of_states[i][0] << endl;
        cout << "States having less transition :-" << endl;
        if(list.size() == list_of_states[i].size()){
            cout << "All states have same number of transitions" << endl;
        }
        else{
            cout << "Minimum number of transitions are = " << count_max << endl;
            for(auto it1 = list.begin(); it1 != list.end(); it1++){
                cout << *it1 << ", ";
            }
            cout << endl;
        } 
        /*for(auto it1 = list.begin(); it1 != list.end(); it1++){
            cout << *it1 << ", ";
        } 
        cout << endl;*/
        cout << endl;
        m++;
    }
    /*int n = transition_of_states.size();
    for(int j = 0; j<n; j++){
        vector<string> v1;
        for(int k = 1; k<transition_of_states[j].size(); k++){
            if(transition_of_states[j][0][k]==1){
                v1.push_back(list_of_states[j][k]);
            }
        }
        /*if(v1.size() != 0){
            output.push_back(v1);
        }
        output.push_back(v1);
    }*/
}

void Rule_R4(vector<vector<string>> &list_of_states, vector<vector<string>> &trig_states){
    regex b2("[a-zA-Z0-9_]*(T|t)(rigger)[a-zA-Z0-9_]*");
    regex b3("[a-zA-Z0-9_]*(T|t)(rig)[a-zA-Z0-9_]*");
    regex b4("[a-zA-Z0-9_]*(TRIGGER)[a-zA-Z0-9_]*");
    regex b5("[a-zA-Z0-9_]*(TRIG)[a-zA-Z0-9_]*");
    for(auto it2 = list_of_states.begin(); it2 != list_of_states.end(); it2++){
        vector<string> v1 = *it2;
        vector<string> v2;
        for(auto it3 = v1.begin(); it3 != v1.end(); it3++){
            if(regex_search(*it3, b2)){
                v2.push_back(*it3);
            }
            else if(regex_search(*it3, b3)){
                v2.push_back(*it3);
            }
            else if(regex_search(*it3, b4)){
                v2.push_back(*it3);
            }
            else if(regex_search(*it3, b5)){
                v2.push_back(*it3);
            }
        }
        trig_states.push_back(v2);
    }
}

void Rule_R3(vector<vector<string>> &list_of_states, vector<vector<string>> &counter_states){
    regex b2("[a-zA-Z0-9_]*(C|c)(ount)[a-zA-Z0-9_]*");
    regex b3("[a-zA-Z0-9_]*(C|c)(nt)[a-zA-Z0-9_]*");
    regex b4("[a-zA-Z0-9_]*(COUNT)[a-zA-Z0-9_]*");
    regex b5("[a-zA-Z0-9_]*(CNT)[a-zA-Z0-9_]*");
    for(auto it2 = list_of_states.begin(); it2 != list_of_states.end(); it2++){
        vector<string> v1 = *it2;
        vector<string> v2;
        for(auto it3 = v1.begin(); it3 != v1.end(); it3++){
            if(regex_search(*it3, b2)){
                v2.push_back(*it3);
            }
            else if(regex_search(*it3, b3)){
                v2.push_back(*it3);
            }
            else if(regex_search(*it3, b4)){
                v2.push_back(*it3);
            }
            else if(regex_search(*it3, b5)){
                v2.push_back(*it3);
            }
        }
        counter_states.push_back(v2);
    }
}

void Rule_R2(vector<string> &input1, vector<vector<string>> &list_of_states, vector<vector<string>> &reset_states){
    /*regex b("(case)[ ]*\\([ ]*[a-zA-Z0-9_]*(s|S)(tate)[a-zA-Z0-9_]*[ ]*\\)[ ]*[begin]*( -> )[0-9]+");
    int count_case = 0;
    vector<string> v;
    for(auto it1 = input1.begin(); it1 != input1.end(); it1++){
        string s1 = *it1;
        if(regex_match(s1, b)){
            count_case++;
        }
        if(count_case > 0){
            regex b1("[a-zA-Z0-9_]+[ ]*\\:");
            if(regex_search(s1, b1)){
                regex b2("[a-zA-Z0-9_]+");
                int pos1 = s1.find(":");
                string state = s1.substr(0, pos1);
                while(state[state.length() - 1] == ' '){
                    state.erase(state.length() - 1);
                }
                if(regex_match(state, b2)){
                    int pos2 = s1.find(" -> ");
                    string line_num = s1.substr(pos2 + 4);
                    if(state != "default"){
                        v.push_back(state + " -> " + line_num);
                    }
                }
            }
        }
        if(s1.find("endcase") != string::npos && count_case > 0){
            count_case--;
            if(v.size() != 0){
                list_of_states.push_back(v);
            }
            v.clear();
        }
    }*/
    regex b2("[a-zA-Z0-9_]*(R|r)(eset)[a-zA-Z0-9_]*");
    regex b3("[a-zA-Z0-9_]*(R|r)(st)[a-zA-Z0-9_]*");
    regex b4("[a-zA-Z0-9_]*(RESET)[a-zA-Z0-9_]*");
    regex b5("[a-zA-Z0-9_]*(RST)[a-zA-Z0-9_]*");
    for(auto it2 = list_of_states.begin(); it2 != list_of_states.end(); it2++){
        vector<string> v1 = *it2;
        vector<string> v2;
        for(auto it3 = v1.begin(); it3 != v1.end(); it3++){
            if(regex_search(*it3, b2)){
                v2.push_back(*it3);
            }
            else if(regex_search(*it3, b3)){
                v2.push_back(*it3);
            }
            else if(regex_search(*it3, b4)){
                v2.push_back(*it3);
            }
            else if(regex_search(*it3, b5)){
                v2.push_back(*it3);
            }
        }
        reset_states.push_back(v2);
    }
}

void Rule_R1(vector<string> &input1, vector<vector<string>> &output1){
    int count1 = 0;
    int count_case = 0;
    int count_default = 0;
    vector<string> v;
    regex b("(default)[ ]*(:)[ ]*[begin]*( -> )[0-9]+");
    regex b2("(default)[ ]*\\:[ ]*");
    regex b1("(case)[ ]*\\([ ]*[a-zA-Z0-9_]*(s|S)(tate)[a-zA-Z0-9_]*[ ]*\\)[ ]*[begin]*( -> )[0-9]+");
    for(auto it1 = input1.begin(); it1 != input1.end(); it1++){
        string s1 = *it1;
        if(regex_match(s1, b1)){
            count_case++;
        }
        else if(count_case > 0){
            if(regex_match(s1, b)){
                count_default++;
            }
            else if(regex_search(s1, b2)){
                count_default++;
            }
        }
        if(count_default > 0){
            if(s1 == "begin"){
                ;
            }
            if(s1.find("end") == 0){
                count_default--;
            }
            else if(s1.find("end") + 3 == s1.find(" -> ")){
                v.push_back(s1);
                //output1.push_back(s1);
                count_default--;
            }
            else{
                v.push_back(s1);
                //output1.push_back(s1);
            }
        }
        if(s1.find("endcase") != string::npos){
            count_case--;
            output1.push_back(v);
        }
    }
}

int getIndex(vector<string> v, string s) 
{ 
    auto it = find(v.begin(), v.end(), s); 
    if (it != v.end())  
    { 
        return it - v.begin(); 
    } 
    else { 
        return -1; 
    } 
} 

vector<vector<vector<int>>> transitions(vector<string> &input1, vector<vector<string>> &list_of_states, vector<int> &position_of_fsm){
    regex b("(case)[ ]*\\([ ]*[a-zA-Z0-9_]*(s|S)(tate)[a-zA-Z0-9_]*[ ]*\\)[ ]*[begin]*( -> )[0-9]+");
    int count_case = 0;
    vector<string> v;
    for(auto it1 = input1.begin(); it1 != input1.end(); it1++){
        string s1 = *it1;
        if(regex_match(s1, b)){
            int pos = s1.find(" -> ");
            int pos_line = stoi(s1.substr(pos+4));
            position_of_fsm.push_back(pos_line);
            count_case++;
        }
        if(count_case > 0){
            regex b1("[a-zA-Z0-9_]+[ ]*\\:");
            if(regex_search(s1, b1)){
                regex b2("[a-zA-Z0-9_]+");
                int pos1 = s1.find(":");
                string state = s1.substr(0, pos1);
                int len1 = state.length();
                while(state[len1 - 1] == ' '){
                    state.erase(len1 - 1);
                    len1 = state.length();
                }
                if(regex_match(state, b2)){
                    int pos2 = s1.find(" -> ");
                    string line_num = s1.substr(pos2 + 4);
                    if(state != "default"){
                        v.push_back(state);
                    }
                }
            }
        }
        if(s1.find("endcase") != string::npos && count_case > 0){
            count_case--;
            if(v.size() != 0){
                list_of_states.push_back(v);
            }
            v.clear();
        }
    }
    /*for(int i = 0; i<list_of_states.size(); i++){
        for(int j = 0; j<list_of_states[i].size(); j++){
            cout << list_of_states[i][j] << " ";
        }
        cout << endl;
    }*/
    int i = 0;
    count_case = 0;
    int n = list_of_states[i].size();
    string cur_state;
    vector<vector<vector<int>>> transition_of_states;
    vector<vector<int>> v1(n, vector<int>(n, 0));
    for(auto it1 = input1.begin(); it1 != input1.end(); it1++){
        string s1 = *it1;
        if(regex_match(s1, b)){
            count_case++;
            //cout << s1 << endl;
        }
        else if(count_case > 0){
            regex b1("[a-zA-Z0-9_]+[ ]*\\:");
            if(regex_search(s1, b1)){
                regex b2("[a-zA-Z0-9_]+");
                int pos1 = s1.find(":");
                string state = s1.substr(0, pos1);
                int len1 = state.length();
                while(state[len1 - 1] == ' '){
                    state.erase(len1 - 1);
                    len1 = state.length();
                }
                if(regex_match(state, b2)){
                    if(state != "default"){
                        cur_state = state;
                        //cout << cur_state << endl;
                    }
                }
            }
            regex b2("[a-zA-Z0-9]*[_]*(n|N)(ext)*[_]*(s|S)(tate)[_]*[a-zA-Z0-9]*");
            regex b3("[a-zA-Z0-9]*[_]*(s|S)(tate)[_]*(n|N)(ext)*[_]*[a-zA-Z0-9]*");
            smatch m;
            if(regex_search(s1,m, b2) || regex_search(s1, m, b3)){
                //cout << s1 << endl;
                for(auto x : m){
                    //cout << x << endl;
                    string nx = x;
                    regex b4("[a-zA-Z0-9]*[_]*(n|N)(ext)*[_]*(s|S)(tate)[_]*[a-zA-Z0-9]*");
                    regex b5("[a-zA-Z0-9]*[_]*(s|S)(tate)[_]*(n|N)(ext)*[_]*[a-zA-Z0-9]*");
                    if(regex_match(nx, b4) || regex_match(nx, b5)){
                        //cout << s1 << endl;
                        int pos1 = s1.find(x) + x.length();
                        int pos2 = s1.find('=', pos1);
                        int pos3 = s1.find(';', pos1);
                        string nstate = s1.substr(pos2+1, pos3 - pos2 - 1);
                        int len = nstate.length();
                        while(nstate[len - 1] == ' '){
                            nstate.erase(len - 1);
                            len--;
                        }
                        while(nstate[0] == ' '){
                            nstate.erase(0, 1);
                        }
                        //cout<< nx << ":" << nstate << endl;
                        int pos_cur_state_in_list = getIndex(list_of_states[i], cur_state);
                        int pos_nstate_in_list = getIndex(list_of_states[i], nstate);
                        //cout << pos_cur_state_in_list << ":" << pos_nstate_in_list << endl;
                        if(pos_cur_state_in_list != -1 && pos_nstate_in_list != -1){
                            //cout << cur_state << ":" << nstate << endl;
                            v1[pos_cur_state_in_list][pos_nstate_in_list] = 1;
                        }
                        v1[pos_cur_state_in_list][pos_nstate_in_list] = 1;
                        //v1[pos_cur_state_in_list][pos_cur_state_in_list] = 1;
                    }
                    break;
                }
            }
        }
        if(s1.find("endcase") != string::npos && count_case > 0){
            count_case--;
            transition_of_states.push_back(v1);
            i++;
            if(i < list_of_states.size()){
                n = list_of_states[i].size();
                vector<vector<int>> v2(n, vector<int>(n, 0));
                v1 = v2;
            }
            if(i >= list_of_states.size()){
                break;
            }
        }
        if(i >= list_of_states.size()){
            break;
        }
    }
    return transition_of_states;
}


void save_input(ifstream& file, vector<string> &input){
    string line;
    int count = 0;
    int count_num = 0;
    while(file){
        getline(file, line);
        if(file.good()){
            count_num++;
            if(line.find("/*") != string::npos && line.find("*/") == string::npos){
                count++;
                int pos = line.find("/*");
                line.erase(pos);
            }
            else if(line.find("/*") != string::npos && line.find("*/") != string::npos){
                int pos1 = line.find("/*");
                int pos2 = line.find("*/");
                line.erase(pos1, pos2 + 2 - pos1);
            }
            else if(count != 0 && line.find("*/") != string::npos){
                int pos = line.find("*/");
                count--;
                line.erase(0, pos + 2);
            }
            else if(count != 0 && line.find("*/") == string::npos){
                line = "";
            }
            else if(line.find("//") != string::npos){
                int pos = line.find("//");
                line.erase(pos);
            }
            while(line[0] == ' ' || line[0] == '\t'){
                line.erase(0, 1);
            }
            while((line[line.length() - 1] == ' ' || line[line.length() - 1] == '\t') && !line.empty()){
                line.erase(line.length() - 1, 1);
            }
            if(!line.empty()){
                line = line + " -> " + to_string(count_num);
                input.push_back(line);
            }
        }
    }
}

int main(){
    cout << "Enter the name of the file" << endl;
    ifstream inFile;
    string name_of_file;
    getline(cin, name_of_file);
    inFile.open(name_of_file);
    vector<string> input;
    save_input(inFile, input);
    inFile.close();
    vector<vector<string>> states;
    vector<vector<vector<int>>> transition_of_states;
    vector<int> position;
    transition_of_states = transitions(input, states, position);
    /*for(int k = 0; k < transition_of_states.size(); k++){
            for(int l = 0; l<transition_of_states[k].size(); l++){
                for(int m = 0; m<transition_of_states[k][l].size(); m++){
                    cout << transition_of_states[k][l][m] << " ";
                }
                cout << endl;
            }
            cout << "next" << endl;
    }*/
    //vector<vector<string>> list;
    //transitions(intput, list);
    //////------------------/////////////
    cout << "::::::::: " << name_of_file <<"::::::::" << endl;
    cout << "/////////////// Output for Rule_R1 /////////////" << endl;
    vector<vector<string>> R1_output;
    Rule_R1(input, R1_output);
    //cout << R1_output.size() << endl;
    if(R1_output.size() == 0){
        cout << "No default state exist" << endl;
    }
    else{
        int k = 0;
        for(int i = 0; i<R1_output.size(); i++){
            cout << "For FSM at position " << position[k] << " default statements" << endl; 
            for(int j = 0; j<R1_output[i].size(); j++){
                cout << R1_output[i][j] << endl;
            }
            k++;
            cout << endl;
        }
        /*for(auto it1 = R1_output.begin(); it1 != R1_output.end(); ++it1){
            //cout << *it1 << endl;
        }*/
    }
    cout << endl;
    cout << "/////////////// Output for Rule_R2 /////////////" << endl;
    //vector<vector<string>> list_of_states;
    vector<vector<string>> reset_states;
    Rule_R2(input, states, reset_states);
    /*for(auto it = states.begin(); it != states.end(); it++){
        vector<string> v1 = *it;
        for(auto it1 = v1.begin(); it1 != v1.end(); it1++){
            cout << *it1 << ", ";
        }
        cout << endl;
    }*/
    if(reset_states.size() == 0){
        cout << "No reset state exist" << endl;
    }
    else{
        int k = 0;
        for(int i = 0; i<reset_states.size(); i++){
            cout << "For FSM at position " << position[k] << " reset states are" << endl; 
            for(int j = 0; j<reset_states[i].size(); j++){
                cout << reset_states[i][j] << endl;
            }
            k++;
            cout << endl;
        }
    }
    cout << endl;
    cout << "/////////////// Output for Rule_R3 /////////////" << endl;
    vector<vector<string>> count_states;
    Rule_R3(states, count_states);
    if(count_states.size() == 0){
        cout << "No count state exist" << endl;
    }
    else{
        int k = 0;
        for(int i = 0; i<count_states.size(); i++){
            cout << "For FSM at position " << position[k] << " count states are" << endl; 
            for(int j = 0; j<count_states[i].size(); j++){
                cout << count_states[i][j] << endl;
            }
            k++;
            cout << endl;
        }
    }
    cout << endl;
    cout << "/////////////// Output for Rule_R4 /////////////" << endl;
    vector<vector<string>> trig_states;
    Rule_R4(states, trig_states);
    if(trig_states.size() == 0){
        cout << "No Trigger state exist" << endl;
    }
    else{
        int k = 0;
        for(int i = 0; i<trig_states.size(); i++){
            cout << "For FSM at position " << position[k] << " trigger states are" << endl; 
            for(int j = 0; j<trig_states[i].size(); j++){
                cout << trig_states[i][j] << endl;
            }
            k++;
            cout << endl;
        }
    }
    cout << endl;
    cout << "/////////////// Output for Rule_R5 /////////////" << endl;
    vector<vector<string>> output_rule_5;
    Rule_R5(transition_of_states, states, position);
    //cout << output_rule_5.size();
    /*int k = 0;
    for(int i = 0; i<output_rule_5.size(); i++){
        cout << "######### In FSM at position " << position[k] << " states having less transitions from initial state are ##########" << endl;
        for(int j = 0; j<output_rule_5[i].size(); j++){
            cout << output_rule_5[i][j] << ", ";
        }
        k++;
        cout << endl;
    }*/
    cout << endl;
    cout << "//////////////// Output for Rule_R6 /////////////////" << endl;
    int i = 0;
    vector<vector<string>> output_rule_r6 = Rule_R6(states, transition_of_states);
    for(auto it = output_rule_r6.begin(); it != output_rule_r6.end(); it++){
        vector<string> v1 = *it;
        if(v1.size() == 0){
            cout << "For FSM at line number " << position[i] << " All state are reachable from initial state" << endl;
        }
        else if(v1.size() == states[i].size() - 1){
            cout << "For FSM at line number " << position[i] << " No state is reachable from initial state" << endl;
        }
        else{
            cout << "For FSM at line number " << position[i] << "State which are reachable from initial state" << endl;
            for(auto it1 = v1.begin(); it1 != v1.end(); it1++){
            cout << *it1 << ", ";
            }
            cout << endl;
        }
        i++;
    }
    cout << endl;
    cout << "//////////////// Output for Rule_R7 /////////////////" << endl;
    vector<vector<string>> rule_7_out;
    Rule_R7(input, states, rule_7_out);
    int j = 0;
    for(auto it = rule_7_out.begin(); it != rule_7_out.end(); it++){
        vector<string> v1 = *it;
        if(v1.size() == 0){
            cout << "For FSM at line number " << position[j] << " No don't care condition exist" << endl;
        }
        else{
            cout << "For FSM at line number " << position[j] << " Don't care conditions" << endl;
            for(auto it1 = v1.begin(); it1 != v1.end(); it1++){
            cout << *it1 << ", ";
            }
            cout << endl;
        }
        j++;
    }
    /*for(int k = 0; k < transition_of_states.size(); k++){
            for(int l = 0; l<transition_of_states[k].size(); l++){
                for(int m = 0; m<transition_of_states[k][l].size(); m++){
                    cout << transition_of_states[k][l][m] << " ";
                }
                cout << endl;
            }
            cout << "next" << endl;
    }
    for(auto it = states.begin(); it != states.end(); it++){
        vector<string> v1 = *it;
        for(auto it1 = v1.begin(); it1 != v1.end(); it1++){
            cout << *it1 << ", ";
        }
        cout << endl;
    }*/
    return 0;
}