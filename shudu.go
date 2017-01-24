package main

import(
    "fmt"
    "time"
)

//行号，列号，数字
/*var in1=[3]int{0,0,1}
var in2=[3]int{6,2,5}
var in3=[3]int{8,8,1}
var in4=[3]int{6,3,1}*/
var num_result=0
//初始化数独信息
func _init()[][3]int{
    var in [][3]int
    var num int
    fmt.Println("请输入初始数字数量：")
    fmt.Scanf("%d\n",&num)
    fmt.Println("请输入位置和数字  x y num：")
    for i:=0;i<num;i++{
        fmt.Printf("请输入第 %d 个：\n",i+1)
        var in1 [3]int
        fmt.Scanf("%d %d %d\n",&in1[0],&in1[1],&in1[2])
        in1[0]-=1
        in1[1]-=1
        in=append(in,in1)
    } 
    return in
}



//根据数独信息初始化数独
func _new(in [][3]int)[9][9]int{
    var shudu [9] [9] int
    for i:=range in{
        shudu[in[i][0]][in[i][1]] = in[i][2]
    }
    return shudu

}

//显示
func show(shudu [9][9]int){
    fmt.Println("  1 2 3   4 5 6   7 8 9")
    for i:=range shudu{
        if i % 3 == 0 && i != 0 {
            fmt.Printf("\n")
        }
        fmt.Printf("%d ",i+1)
        for j:=range shudu[i]{
           if j % 3 == 0 && j != 0{
               fmt.Printf("  ")
           }
           if shudu[i][j]==0{
               fmt.Printf("  ")
           }else{
               fmt.Printf("%d ",shudu[i][j])
           }
        }
        fmt.Printf("\n")
    }
}


func make_lack(shudu [9][9]int,x int,y int)(num_lack []int,lack int){
    if shudu[x][y]!=0{
        lack=10
        return 
    }
    lack=9
    var nums []int
    var in_nums bool
    in_nums=false
    //行
    for i:=range shudu[x]{
        if shudu[x][i]!=0{
            for j:=range nums{
                if shudu[x][i]==nums[j]{
                    in_nums=true
                    break
                }
            }
            if !in_nums{
                nums=append(nums,shudu[x][i])
                lack--
            }
        }  
    }

    //列
    for i:=0;i<9;i++{
        if shudu[i][y]!=0{
            for j:=range nums{
                if shudu[i][y]==nums[j]{
                    in_nums=true
                    break
                }
            }
            if !in_nums{
                nums=append(nums,shudu[i][y])
                lack--
            }
        }  
    }

    //块
    k:=x/3*3;
    m:=y/3*3
    for n:=0;n<3;n++{
    for i:=0;i<3;i++{
        if shudu[k][m+i]!=0{
            for j:=range nums{
                if shudu[k][m+i]==nums[j]{
                    in_nums=true
                    break
                }
            }
            if !in_nums{
                nums=append(nums,shudu[k][m+i])
                lack--
            }
        }  
    }
    k++
    }
    var in_lack bool
    for i:=1;i<10;i++{
        in_lack=false
        for j:=range nums{
            if i== nums[j]{
                in_lack=true
                break
            }
        }
        if !in_lack{
            num_lack=append(num_lack,i)
        }
    }
    return
}

//制作一个9x9的数组，里面放的是数独的每个格子可选的数量
func make_all_lack(shudu [9][9]int)[9][9]int{
    var all_lack [9][9]int
    for i:=range shudu{
        for j:=range shudu[i]{
            _,all_lack[i][j]=make_lack(shudu,i,j)
        }
    }
    return all_lack
}

func isfull(shudu [9][9]int)(bool){
    for i:=range shudu{
        for j:=range shudu[i]{
            if shudu[i][j]==0{
                return false
            }
        }
    }
    return true
}

func min_lack(lack [9][9]int)(x int ,y int){
    n:=10
    for i:=range lack{
        for j:=range lack[i]{
            if lack[i][j]==1{
                x=i
                y=j
                return 
            }else if lack[i][j]<n{
                x=i
                y=j
                n=lack[i][j]
            }
        }
    }
    return
}


//填充数独
func _make(shudu [9][9]int){
    
    
    if isfull(shudu){
        num_result++
        fmt.Printf("\n第 %d 个数独\n",num_result)
        show(shudu)
        time.Sleep(1000000000)
        return
    }
    all_lack:=make_all_lack(shudu)
    x,y:=min_lack(all_lack)
    list,_:=make_lack(shudu,x,y)
    for _,i:=range list{
        //fmt.Printf("x: %d  y: %d  i: %d \n",x,y,i)
        shudu[x][y]=i
        _make(shudu)
    }
}


func main(){
    in:=_init()
    shudu:=_new(in)
    _make(shudu)
}