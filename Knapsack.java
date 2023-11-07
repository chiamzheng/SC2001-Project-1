package proj3;

public class Knapsack {
	
	//Attributes
	public Item[] itemArr;
	public int maxCapacity;
	public int [][] profit; //Dictionary
	
	//Constructor
	public Knapsack(Item[] itemArr, int maxCapacity) {
		this.itemArr = itemArr;
		this.maxCapacity = maxCapacity;
		this.profit = new int[itemArr.length + 1][maxCapacity + 1]; //Initialize a 2D Array of size[n+1][m+1]
		
		//Initialize the 2D array elements as 0
		for (int i = 0; i < itemArr.length; i++) {
            for (int j = 0; j < maxCapacity; j++) {
                this.profit[i][j] = 0;
            }
        }
	}
	
	public int dynamicProgramming(int capacity) {
		
		//Base Case / Trivial Case when index/item or remaining capacity == 0
		for (int c = 0; c < maxCapacity; c++) {
			profit[0][c] = 0;
		}
		for (int r = 1; r < itemArr.length; r++) { //Start from r=1 as we already did column 0
			profit[r][0] = 0;
		}
		
		for (int i=1; i<= itemArr.length; i++) {
			for (int c=1; c<=maxCapacity; c++) {
				
				if (itemArr[i-1].weight <= c) {
					int exclude = profit[i-1][c];
					int include = profit[i][c-itemArr[i-1].weight] + itemArr[i-1].value;
					
					if (exclude > include) {
						profit[i][c] = exclude;
					}
					else {
						profit[i][c] = include;
					}
				}
				else {
					profit[i][c] = profit[i-1][c];
				}
			}
		}

		return profit[itemArr.length][maxCapacity];
	}
	
	public void printProfitTable() {
        for (int i = 0; i < profit.length; i++) {
            var p = profit[i];
            for (int j = 0; j < p.length; j++) {
                System.out.print(p[j] + " ");
            }
            System.out.println();
        }
    }
}
