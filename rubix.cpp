#include<vector>
#include<string>
#include<iostream>

#include<algorithm>



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

    public:

    rubix(): red(9, 'R'), white(9, 'W'), orange(9, 'O'), yellow(9, 'Y'), green(9, 'G'), blue(9, 'B'),f_front(&red), f_back(&orange), f_left(&green), f_right(&blue), f_upper(&white), f_lower(&yellow)
    {
      
    };

    //utility

    void swap(std::vector<char> &veca, std::vector<char> &vecb, std::vector<std::pair<int,int>> pos )
    {
        for(const auto & [pa,pb]:pos)
        {
            std::swap(veca[pa],vecb[pb]);

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

    //moves

    void rotate(std::vector<char> &face,bool clockwise, int n=1)
    {
        if(n==1)
        {
            if(clockwise)  swap(face,{{0,2},{0,8},{0,6},{1,5},{1,7},{1,3}});  //
            else           swap(face,{{0,6},{0,8},{0,2},{1,3},{1,7},{1,5}});
        }
        else swap(face,{{0,8},{1,7},{2,6},{3,5}});

    }

    void up(int n,int col)
    {
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
    void down(int n,int col)
    {
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

    void right(int n,int row)
    {
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
    
    void left(int n,int row)
    {
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

    void clockw(int n, int pos)
    {
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
    
    void antclockw(int n, int pos)
    {
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
            std::swap(f_front,f_back);

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
        down(n,0);
        down(n,1);
        down(n,2);

    }
    void roll_right(int n)
    {
        clockw(n,0);
        clockw(n,1);
        clockw(n,2);

    }
    void roll_left(int n)
    {
        antclockw(n,0);
        antclockw(n,1);
        antclockw(n,2);

    }
    void turn_right(int n)
    {
        right(n,0);
        right(n,1);
        right(n,2);

    }
    void turn_left(int n)
    {
        left(n,0);
        left(n,1);
        left(n,2);

    }

    //plays

    void test()
    {
        // red={'a','b','c','d','e','f','g','h','i'};
        print_all();

      
    };
    


};



int main()
{
    rubix rubix1;

    rubix1.test();



    std::cout<<"eeeennnnddd\n";

    

    

    return 0;

}

// sdfgjjjjjjjjjjjjjjjjjj
////sdfgjjjjjjjjjjjjjjjjjj
