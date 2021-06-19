class Cricket {
		static double addscore() {
			int min=0,max=110;
			return (Math.random() * (max - min + 1)) + min; 
		}
	public static void main(String[] args) {
		int[] score_arr=new int[11];
		int i=0;
		String j="";
		for(i=0;i<11;i++) {
			score_arr[i] = (int)addscore();
		}
		for(i=0;i<11;i++) {
			j=(score_arr[i]<=9) ? "bad" : 
				(score_arr[i]<=99) ? "good" :
					"very good";
			System.out.println("a["+i+"]: "+ j);
		}
	}
}
