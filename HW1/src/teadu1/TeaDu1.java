package teadu1;

import java.util.ArrayList;
import java.util.Scanner;

/**
 *
 * @author Miklosovic
 */



class TeaDu1 {
    
    static class Helper{
        public int left, right, count;
    }
    
    static void init(ArrayList<Helper> array, int size){
        for(int i = 0; i < (2*size); ++i){
            array.add(new Helper());
        }
        
        for(int i = 0; i < size; ++i){
            array.get(2*size - 1 - i).left = size - i;
            array.get(2*size - 1 - i).right = size - i;
        }
        for(int i = size- 1; i > 0; --i){
            array.get(i).left = array.get(2*i).left;
            array.get(i).right = array.get(2*i + 1).right;
        }

        for(int i = 0; i < array.size(); ++i){
            array.get(i).count = 0;
        }
        
        
    }
    static void update(int left, int right, int nodeId, ArrayList<Helper> array){
        Helper hp = array.get(nodeId);
        if((hp.left >= left)&&(hp.right <= right)){
            hp.count += 1;
            return;
        }
        
        if((hp.right < left)||(hp.left > right)){
            return;
        }
        
        update(left, right, nodeId*2, array);
        update(left, right, (nodeId*2)+1, array);
    }
    
    static boolean inside(int left, int right, int i){
        return (i >= left)&&(i <= right);
    }
    
    static int query(int i, int nodeId, ArrayList<Helper> array){       
        if(nodeId >= array.size()){
            return 0;
        }
        Helper hp = array.get(nodeId);
        if(inside(hp.left, hp.right, i)){
            return hp.count + query(i, nodeId*2, array) + query(i, (nodeId*2) + 1, array);
        }
        else{
            return 0;
        }
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Scanner in =  new Scanner(System.in);
        int numOfLeaves = in.nextInt();
        int numOfQueries = in.nextInt();
        int size = (int)Math.pow(2, Math.ceil(Math.log(numOfLeaves)/Math.log(2)));
        
        ArrayList<Helper> array = new ArrayList<>();
        init(array, size);
        for(int i = 0; i < numOfQueries; ++i){
            int q = in.nextInt();
            if(q == 1){// get number of intervals intersecting with nextInt
                int pos = in.nextInt();
                System.out.println(query(pos, 1, array));
            }
            if(q == 2){// insert interval from left to right
                int left = in.nextInt();
                int right = in.nextInt();
                update(left, right, 1, array);
            }
        }
       
    }
    
    
    
}
