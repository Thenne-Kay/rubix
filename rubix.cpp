#include<vector>
#include<string>
#include<iostream>

#include<algorithm>

#include<unordered_map>

class edge
{
    public:
    int a;
    int b;
    std::vector<char> *&col_a;
    std::vector<char> *&col_b;

    edge(std::vector<char> *&vec_a, std::vector<char> *&vec_b) : col_a(vec_a), col_b(vec_b)
    {
       
    }

    void set_ptr( std::vector<char>* &vec_a, std::vector<char>* &vec_b)
    {
        col_a=vec_a;
        col_b=vec_b;
    }

    void set_index(int a,int b)
    {
        this->a=a;
        this->b=b;
    }

    std::vector<char> get_colr()
    {

        return {(*col_a)[a],(*col_b)[b]};
    }

};

class corner
{
    public:
    int a;
    int b;
    int c;
    std::vector<char> *&col_a;
    std::vector<char> *&col_b;
    std::vector<char> *&col_c;

    corner(std::vector<char> *&vec_a, std::vector<char> *&vec_b, std::vector<char> *&vec_c) : col_a(vec_a), col_b(vec_b), col_c(vec_c)
    {

    }

    void set_ptr( std::vector<char>* &vec_a, std::vector<char>* &vec_b,std::vector<char>* &vec_c)
    {
        col_a=vec_a;
        col_b=vec_b;
        col_c=vec_c;

    }

    void set_index(int a,int b, int c)
    {
        this->a=a;
        this->b=b;
        this->c=c;
    }

    std::vector<char> get_colr()
    {
       
        return {(*col_a)[a],(*col_b)[b],(*col_c)[c]};
    }

};


class rubix 
{
    std::vector<char> red;
    std::vector<char> orange;
    std::vector<char> green;
    std::vector<char> blue;
    std::vector<char> white;
    std::vector<char> yellow;

    std::vector<char>* f_front;
    std::vector<char>* f_back;
    std::vector<char>* f_left;
    std::vector<char>* f_right;
    std::vector<char>* f_upper;
    std::vector<char>* f_lower;

    std::unordered_map<int,int> piece_pos;


    edge edge0;
    edge edge1;
    edge edge2;
    edge edge3;
    edge edge4;
    edge edge5;
    edge edge6;
    edge edge7;
    edge edge8;
    edge edge9;
    edge edge10;
    edge edge11;

    corner corner0;
    corner corner1;
    corner corner2;
    corner corner3;
    corner corner4;
    corner corner5;
    corner corner6;
    corner corner7;

    

    std::vector<edge*> edges{&edge0, &edge1, &edge2, &edge3, &edge4, &edge5, &edge6, &edge7 ,&edge8, &edge9, &edge10, &edge11};
    std::vector<corner*> corners{&corner0, &corner1, &corner2, &corner3, &corner4, &corner5, &corner6, &corner7 };


    std::vector<std::vector<int>> moves_made;
    std::vector<std::vector<std::vector<int>>> soln;

    std::vector<char> plane_moves={'R','U','F'};
    std::vector<int> level_moves={0,2};
    std::vector<int> turn_moves={1,2,-1};



    public:
        rubix() : red(9, 'R'), white(9, 'W'), orange(9, 'O'), yellow(9, 'Y'), green(9, 'G'), blue(9, 'B'), f_front(&red), f_back(&orange), f_left(&green), f_right(&blue), f_upper(&white), f_lower(&yellow),
                  edge0(f_front, f_left), edge1(f_front, f_upper), edge2(f_front, f_right), edge3(f_front, f_lower), 
                  edge4(f_upper, f_left), edge5(f_upper, f_right), edge6(f_lower, f_right), edge7(f_lower, f_left),
                  edge8(f_back, f_left), edge9(f_back, f_upper), edge10(f_back, f_right), edge11(f_back, f_lower),
                  corner0(f_front, f_left, f_upper), corner1(f_front, f_upper, f_right), corner2(f_front, f_right, f_lower), corner3(f_front, f_lower, f_left),
                  corner4(f_back, f_upper ,f_left), corner5(f_back, f_right, f_upper), corner6(f_back, f_lower ,f_right), corner7(f_back, f_left, f_lower)

        {
            edge0.set_index(3,5);
            edge1.set_index(1,7);
            edge2.set_index(5,3);
            edge3.set_index(7,1);

            edge4.set_index(3,1);
            edge5.set_index(5,1);
            edge6.set_index(5,7);
            edge7.set_index(3,7);

            edge8.set_index(3,3);
            edge9.set_index(7,1);
            edge10.set_index(5,5);
            edge11.set_index(1,7);

            corner0.set_index(0,6,2);
            corner1.set_index(2,8,0);
            corner2.set_index(8,2,6);
            corner3.set_index(6,0,8);

            corner4.set_index(6,0,0);
            corner5.set_index(8,2,2);
            corner6.set_index(2,8,8);
            corner7.set_index(0,6,6);
        };

        // utility

    void swap(std::vector<char> &veca, std::vector<char> &vecb, std::vector<std::pair<int, int>> pos)
        {
            for (const auto &[pa, pb] : pos)
            {
                std::swap(veca[pa], vecb[pb]);
            }

    }
    void swap(std::vector<char> &veca, std::vector<std::pair<int,int>> pos )
    {
        for(const auto & [pa,pb]:pos)
        {
            std::swap(veca[pa],veca[pb]);

        }

    }

    void print(std::vector<char>& face)
    {

        for(int i=0;i<9;i++)
        {
            std::cout<<face[i]<<"  ";

            if(i%3==2) std::cout<<"\n";

        }

        std::cout<<"\n";


    }

    void print_all()
    {
        print(*f_front);
        print(*f_upper);
        print(*f_back);
        print(*f_lower);
        print(*f_left);
        print(*f_right);
    }

    void reset()
    {
        red=std::vector<char>(9, 'R');
        white=std::vector<char>(9, 'W');
        orange=std::vector<char>(9, 'O');
        yellow=std::vector<char>(9, 'Y');
        green=std::vector<char>(9, 'G');
        blue=std::vector<char>(9, 'B');
    }

    void set_piece_pos()
    {

        int n=0;
        for(auto* &edge_cube:edges)
        {
           int a=(*edge_cube->col_a)[4];
           int b=(*edge_cube->col_b)[4];

           piece_pos[(a*b)/10]=n;
           n++;

        }

        n=0;

        for(auto* &corner_cube:corners)
        {
           int a=(*corner_cube->col_a)[4];
           int b=(*corner_cube->col_b)[4];
           int c=(*corner_cube->col_c)[4];

           piece_pos[(a*b*c)/1000]=n;
           n++;

        }




    }



    bool edge_parity()
    {
        std::unordered_map<char,bool> pri_col;
        pri_col[(*f_front)[4]]=1;
        pri_col[(*f_back)[4]]=1;

        std::unordered_map<char,bool> sec_col;
        sec_col[(*f_upper)[4]]=1;
        sec_col[(*f_lower)[4]]=1;

        bool parity=1;


        // lamba function to check an edge
        auto is_counted=[&pri_col,&sec_col](std::vector<char> col_pair)
        {
            return pri_col[col_pair[0]] || (sec_col[col_pair[0]] && !pri_col[col_pair[1]]);

        };

        for(auto* &edge_cube :edges)
        {
             parity=  is_counted(edge_cube->get_colr()) ?   !parity : parity ;

        }

        return parity;

        

    }

    bool corner_parity()
    {
        std::unordered_map<char, bool> pri_col;
        pri_col[(*f_front)[4]] = 1;
        pri_col[(*f_back)[4]] = 1;

        int count=0;

       

        bool parity = 1;

        // lamba function to check an edge
        auto is_counted = [&pri_col](std::vector<char> col_tri)
        {
            if(pri_col[col_tri[0]]) return 0;
            
            return pri_col[col_tri[1]] ?   1:-1;

        };

        for(auto* &corner_cube: corners)
        {
            count+= is_counted(corner_cube->get_colr());

        }

        return count%3==0;


    }

    bool permutation_parity()
    {
        set_piece_pos();

        std::vector<int> edge_swap(12);
        std::vector<int> corner_swap(8);
        
        int n=0;
        int pos=0;
        for (auto *&corner_cube : corners)
        {
            std::vector<char> keys=corner_cube->get_colr();
            int prime_key=keys[0]*keys[1]*keys[2];
            int pos=piece_pos[prime_key/1000];

            corner_swap[n++]=pos;


        }

        n=0;
        pos=0;
        for (auto *&edge_cube : edges)
        {
            std::vector<char> keys=edge_cube->get_colr();
            int prime_key=keys[0]*keys[1];
            int pos=piece_pos[prime_key/10];

            corner_swap[n++]=pos;


        }

        n=0;

        for(int i=0;i<8;i++)
        {
            while(i!=corner_swap[i])
            {
                std::swap(corner_swap[i], corner_swap[corner_swap[i]]);
                n++;
            }


        }

        for(int i=0;i<12;i++)
        {
            while(i!=edge_swap[i])
            {
                std::swap(edge_swap[i], edge_swap[edge_swap[i]]);
                n++;
            }

        }


        return n%2==0;



    }

    //     2 solved opposite layers and 3 of the remaining edges(from 4) is optimal
    //     3 faces in a horseshoe and a missing edge(from 2)
    //     3 orthogonal faces and 2 of the missing edges(from 3)
    //             Beyond this :
    //     Any combination of 4 faces involves one of the above cases.
    // this algorithim uses the  horseshoe meth0d 
    bool issolved()
    {

        auto is_face_solved = [&](std::vector<char>& face)
        {
            for(auto & sticker : face)
            {
                if(sticker !=face[4]) return false;

            }

            return true;
           
        };

        bool solved=is_face_solved(*f_front) && is_face_solved(*f_upper) && is_face_solved(*f_lower);
        
        return solved && (*f_left)[7]==(*f_left)[4];



    }
    //* solving essentials

    void randomize()
    {

    }

    //move = plane level turns 
    // plane R F U
    // level(0,1), 1 means inversion of plane eg R=L
    // negative turn means inversion of move R=R'
    void decode_move(char& plane, int& level, int& n)
    {
        if(plane=='R') up(n,2-level);
        else if (plane=='U') right(n,level);
        else if (plane=='F') clockw(n,2-level);

    }

    void reverse_move(char plane, int level, int n)
    {
        if(plane=='R') up(-n,2-level);
        else if (plane=='U') right(-n,level);
        else if (plane=='F') clockw(-n,2-level);

    }

   

    bool is_move_valid(char& plane, int& level)
    {
        int sz=moves_made.size();
        if(sz==0) return 1;

        if(moves_made[sz-1][0]!=plane) return 1;

        // wrong , adjust later
        bool same_level=0;
        for(int x=sz-1;x>=0 && moves_made[x][0]==plane;x--)
        {
            same_level= (moves_made[x][1]==level);

            if(same_level) return 0;

        }


        return 1;

    }

    int paths=0;

    int dfs_solve(int limit=20,int count=0)
    { 
        if(issolved())
        {
            soln.push_back(moves_made);
            paths++;
            return count;
        }

        if(count>=limit) {paths++;return limit;}

        for(auto& plane : plane_moves)
        {
            for(auto& level : level_moves)
            {
                for(auto& turn : turn_moves)
                {
                    if(is_move_valid(plane,level))
                    {
                        decode_move(plane,level,turn);
                        moves_made.push_back({plane,level,turn});
                        limit=dfs_solve(limit, count+abs(turn));

                        reverse_move(plane,level,turn);
                        moves_made.pop_back();

                        if(count+1==limit && soln.size()!=0) return limit;

                    }

                }

            }

        }

        paths++;
        return limit;
        
    }

    int solve_cube(int limit=20)
    {
        moves_made.clear();
        soln.clear();

        return dfs_solve(limit);

    }

    void print_soln()
    {
        for(auto& ans : soln)
        {
            std::cout<<"beginning of new soln:\n";

            for(auto& move : ans)
            {
                std::cout<<char(move[0])<<move[1]<<" "<<move[2]<<"\n";

            }

        }

    }

    
    //*moves

    void rotate(std::vector<char> &face,bool clockwise, int n=1)
    {
        if(n==1)
        {
            if(clockwise)  swap(face,{{0,2},{0,8},{0,6},{1,5},{1,7},{1,3}});  //
            else           swap(face,{{0,6},{0,8},{0,2},{1,3},{1,7},{1,5}});
        }
        else swap(face,{{0,8},{1,7},{2,6},{3,5}});

    }

    // R(n,2)  L(n,0)
    void up(int n,int col)
    {

        if(n<0) 
        {
            down(n*-1,col);
            return;        
        
        }

        if(n==2)
        {
            swap(*f_front,*f_back,{{col,col},{col+3,col+3},{col+6,col+6}});  
            swap(*f_lower,*f_upper,{{col,col},{col+3,col+3},{col+6,col+6}});
        }

        else if(n==1)
        {
            swap(*f_front,*f_upper,{{col,col},{col+3,col+3},{col+6,col+6}});    //036 036  147 147  258 258
            swap(*f_front,*f_back,{{col,col},{col+3,col+3},{col+6,col+6}});
            swap(*f_front,*f_lower,{{col,col},{col+3,col+3},{col+6,col+6}});

        }

        if(col==0) rotate(*f_left,0,n);
        else if(col==2) rotate(*f_right,1,n);
        

    }

    // R'(n,2)  l'(n,0)
    void down(int n,int col)
    {
        if(n<0) 
        {
            up(n*-1,col);
            return;        
        
        }


        if(n==2)
        {
            swap(*f_front,*f_back,{{col,col},{col+3,col+3},{col+6,col+6}});
            swap(*f_lower,*f_upper,{{col,col},{col+3,col+3},{col+6,col+6}});
        }

        else if(n==1)
        {
            swap(*f_front,*f_lower,{{col,col},{col+3,col+3},{col+6,col+6}});
            swap(*f_front,*f_back,{{col,col},{col+3,col+3},{col+6,col+6}});
            swap(*f_front,*f_upper,{{col,col},{col+3,col+3},{col+6,col+6}});

        }

        if(col==0) rotate(*f_left,1,n);
        else if(col==2) rotate(*f_right,0,n);
        

    }

    // U(n,0)     d(n,2)
    void right(int n,int row)
    {

        if (n < 0)
        {
            left(n * -1, row);
            return;
        }


        if(n==2)
        {
            swap(*f_front,*f_back,{{3*row,6-(3*row)+2},{3*row+1,6-(3*row)+1},{3*row+2,6-(3*row)}});  //012,876  345 543  678 210
            swap(*f_left,*f_right,{{3*row,3*row},{3*row+1,3*row+1},{3*row+2,3*row+2}});  //012,678  345 345  678 012
        }

        else if(n==1)
        {
            swap(*f_front,*f_right,{{3*row,3*row},{3*row+1,3*row+1},{3*row+2,3*row+2}});  //012,012  345 345  678 678
            swap(*f_front,*f_back,{{3*row,6-(3*row)+2},{3*row+1,6-(3*row)+1},{3*row+2,6-(3*row)}});  //012,876  345 543  678 210
            swap(*f_front,*f_left,{{3*row,3*row},{3*row+1,3*row+1},{3*row+2,3*row+2}});  //012,012  345 345  678 678
            

        }

        if(row==0) rotate(*f_upper,0,n);
        else if(row==2) rotate(*f_lower,1,n);
        

    }
    
    // u'(n,0)     d'(n,2)
    void left(int n,int row)
    {
        if(n<0) 
        {
            right(n*-1,row);
            return;        
        
        }


        if(n==2)
        {
            swap(*f_front,*f_back,{{3*row,6-(3*row)+2},{3*row+1,6-(3*row)+1},{3*row+2,6-(3*row)}});  //012,876  345 543  678 210 //*error
            swap(*f_left,*f_right,{{3*row,3*row},{3*row+1,3*row+1},{3*row+2,3*row+2}});  //012,678  345 345  678 012
        }

        else if(n==1)
        {
            swap(*f_front,*f_left,{{3*row,3*row},{3*row+1,3*row+1},{3*row+2,3*row+2}});  //012,012  345 345  678 678
            swap(*f_front,*f_back,{{3*row,6-(3*row)+2},{3*row+1,6-(3*row)+1},{3*row+2,6-(3*row)}});  //012,876  345 543  678 210
            swap(*f_front,*f_right,{{3*row,3*row},{3*row+1,3*row+1},{3*row+2,3*row+2}});  //012,012  345 345  678 678
            
        }

        if(row==0) rotate(*f_upper,1,n);
        else if(row==2) rotate(*f_lower,0,n);
        

    }

    // f(n,2)   b(n,0)
    void clockw(int n, int pos)
    {
        if(n<0) 
        {
            antclockw(n*-1,pos);
            return;        
        
        }



        if(n==2)
        {
            swap(*f_upper,*f_lower,{{3*pos,6-(3*pos)+2},{3*pos+1,6-(3*pos)+1},{3*pos+2,6-(3*pos)}});  //012 876  345 543  678 210
            swap(*f_left,*f_right,{{pos,2-pos+6},{pos+3,2-pos+3},{pos+6,2-pos}});  //036 852   147 741 258 630

        }

        else
        {
            swap(*f_upper,*f_right,{{3*pos,2-pos},{3*pos+1,2-pos+3},{3*pos+2,2-pos+6}}); //012 258   345 147    678 036
            swap(*f_upper, *f_lower, {{3*pos, 6-(3*pos)+2}, {3*pos+1, 6-(3*pos)+1}, {3*pos+2, 6-(3*pos)}}); // 012 876   345 543    678 210
            swap(*f_upper,*f_left,{{3*pos,pos+6},{3*pos+1,pos+3},{3*pos+2,pos}}); //012 630   345 741    678 852

        }

        if(pos==0) rotate(*f_back,0,n);
        else if(pos==2) rotate(*f_front,1,n);
        

    }
    
    // f'(n,2)   b'(n,0)
    void antclockw(int n, int pos)
    {
        if(n<0) 
        {
            clockw(n*-1,pos);
            return;        
        
        }
        if(n==2)
        {
            swap(*f_left,*f_right,{{pos,2-pos+6},{pos+3,2-pos+3},{pos+6,2-pos}});  //036 852   147 741 258 630
            swap(*f_upper,*f_lower,{{3*pos,6-(3*pos)+2},{3*pos+1,6-(3*pos)+1},{3*pos+2,6-(3*pos)}});  //012 876  345 543  678 210

        }

        else
        {
            swap(*f_upper,*f_left,{{3*pos,pos+6},{3*pos+1,pos+3},{3*pos+2,pos}}); //012 630   345 741    678 852
            swap(*f_upper, *f_lower, {{3*pos, 6-(3*pos)+2}, {3*pos+1, 6-(3*pos)+1}, {3*pos+2, 6-(3*pos)}}); // 012 876   345 543    678 210
            swap(*f_upper,*f_right,{{3*pos,2-pos},{3*pos+1,2-pos+3},{3*pos+2,2-pos+6}}); //012 258   345 147    678 036

        }

        if(pos==0) rotate(*f_back,1,n);
        else if(pos==2) rotate(*f_front,0,n);
        

    }

    //*create references to address the faces
    //*switch references rather than the data

    void roll_frd(int n)
    {
        
        if(n==1)
        {
            
            std::swap(f_front,f_upper);
            std::swap(f_front,f_back);
            std::swap(f_front,f_lower);

        }

        else
        {
            std::swap(f_front, f_back);
            std::swap(f_upper, f_lower);
        }
        
        rotate(*f_left,0,n);
        rotate(*f_right,1,n);

    }

    void roll_bck(int n)
    {
        
        if(n==1)
        {
            
            std::swap(f_front,f_lower);
            std::swap(f_front,f_back);
            std::swap(f_front,f_upper);

        }

        else
        {
            std::swap(f_front, f_back);
            std::swap(f_upper, f_lower);
        }
        
        rotate(*f_left,1,n);
        rotate(*f_right,0,n);

    }
   
    void roll_right(int n)
    {
        
        if(n==1)
        {
            std::swap(f_upper,f_right);
            std::swap(f_upper,f_lower);
            std::swap(f_upper,f_left);

            rotate(*f_upper,1,1);
            rotate(*f_right,1,1);
            rotate(*f_lower,1,1);
            rotate(*f_left,1,1);

        }

        else
        {
            std::swap(f_upper,f_lower);
            std::swap(f_left,f_right);

            rotate(*f_lower,1,2);
            rotate(*f_upper,1,2);
            rotate(*f_right,1,2);
            rotate(*f_left,1,2);

        }

        rotate(*f_front,1,n);
        rotate(*f_back,0,n);



    }

    void roll_left(int n)
    {
        
        if(n==1)
        {
            std::swap(f_upper,f_left);
            std::swap(f_upper,f_lower);
            std::swap(f_upper,f_right);

            rotate(*f_upper,0,1);
            rotate(*f_right,0,1);
            rotate(*f_lower,0,1);
            rotate(*f_left,0,1);

        }

        else
        {
            std::swap(f_upper,f_lower);
            std::swap(f_left,f_right);

            rotate(*f_lower,1,2);
            rotate(*f_upper,1,2);
            rotate(*f_right,1,2);
            rotate(*f_left,1,2);

        }

        rotate(*f_front,0,n);
        rotate(*f_back,1,n);


    }
   
    void turn_right(int n)
    {
        if(n==1)
        {
            std::swap(f_front,f_right);
            std::swap(f_front,f_back);
            std::swap(f_front,f_left);

            rotate(*f_back,1,2);
            rotate(*f_left,1,2);

        }
        else
        {
            std::swap(f_front,f_back);
            std::swap(f_left,f_right);

            rotate(*f_back,1,2);
            rotate(*f_front,1,2);

        }

        rotate(*f_upper,0,n);
        rotate(*f_lower,1,n);


    }

    void turn_left(int n)
    {
        if(n==1)
        {
            std::swap(f_front,f_left);
            std::swap(f_front,f_back);
            std::swap(f_front,f_right);

            rotate(*f_back,1,2);
            rotate(*f_right,0,2);

        }
        else
        {
            std::swap(f_front,f_back);
            std::swap(f_left,f_right);

            rotate(*f_back,1,2);
            rotate(*f_front,1,2);

        }

        rotate(*f_upper,1,n);
        rotate(*f_lower,0,n);


    }
   

    //plays

    void test()
    {
        // red[1]='W';
        // white[1]='O';
        // white[7]='R';
        // orange[7]='W';

        up(1,2);
        right(2,0);

        print_all();
        solve_cube(20);

        std::cout<<"START OF SOLUTION\n";
        print_soln();
        
    };
    


};



int main()
{
    rubix rubix1;

    rubix1.test();

    int a=4;
    int& refa=a;



    std::cout<<"eeeennnnddd\n";

    

    

    return 0;

}

// sdfgjjjjjjjjjjjjjjjjjj
////sdfgjjjjjjjjjjjjjjjjjj
