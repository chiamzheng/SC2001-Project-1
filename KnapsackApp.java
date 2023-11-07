package proj3;

public class KnapsackApp {
	
	public static void main(String[] args) {
		
        int capacity = 14;
		
		Item[] items = new Item[]{
                new Item(4, 7),
                new Item(6, 6),
                new Item(8, 9),
        };
        Knapsack knapsack = new Knapsack(items, capacity);

        Item[] items1 = new Item[]{
                new Item(5, 7),
                new Item(6, 6),
                new Item(8, 9),
        };
        Knapsack knapsack1 = new Knapsack(items1, capacity);
		
        printResult(capacity, knapsack.dynamicProgramming(capacity));
        knapsack.printProfitTable(); 
        printResult(capacity, knapsack1.dynamicProgramming(capacity));
        knapsack1.printProfitTable(); 
	}
	
	
	private static void printResult(int capacity, int result) {
        System.out.println("Capacity: " + capacity);
        System.out.println("Max Profit: " + result + "\n");
    }
	
}
