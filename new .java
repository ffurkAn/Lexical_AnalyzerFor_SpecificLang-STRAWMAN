import java.util.Vector;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

/**
 * @author Gergefil
 * @author Gülügül
 */
public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		System.out.println("Külyutmaz 1.0");
		System.out.println("Lexical Analyzer and TOPALOGLU++ Languange Parser");
		System.out.println("05-06-7699 Umut BENZER");
		System.out.println("05-06-7670 Gül DELYORMAN\n");
		
		String girdi = new String();
		try {
			final BufferedReader in = new BufferedReader(new FileReader("text.txt"));
			String txt = null;
			while ((txt = in.readLine()) != null) {
				girdi = girdi + txt;
			}
			in.close();
		} catch (final IOException e) {
			System.out.println("Erör: text.txt dosyasy okunamady. Lütfen bilgisayarynyzy camdan a?a?y atynyz! :)");
			System.exit(0);
		}
		
		String one_word= "";
		for(int i = 0; i<girdi.length();i++) { /* Bu kysymda satyr satyr ayry?tyryryz. */
			if(girdi.charAt(i) == ';') {
				System.out.println("\n\nSyradaki komut: " + one_word + ';');
				
				int sayac = 0;
				String temp = "";
				String left = "";
				String right = "";
				boolean cik = false;
				
				for(int x = 0; x<one_word.length();x++) { /* Bir satyr gezilir ve sa? ve sol de?i?kenlerine ayry?tyrylyr. */
					if(one_word.charAt(x) == ':' && one_word.length() > x  && one_word.charAt(x+1) == '=') {						
						if (sayac==0) { 
							left = temp;
							/* System.out.println("Sol: " + left + "|"); // Kodun sol kysmyny görmek için commenti kaldyryn. */
							temp = "";
							x++;
						} else { 
							System.out.println("Erör: Satyrda birden çok := atamasy var!");
							cik = true;
							break;
						}
						sayac++;	
					} else {
						temp = temp + one_word.charAt(x);						
					}
				}
				if (cik == true) {one_word = ""; continue; }/* E?er := hatasy varsa daha ne kontrol edeyim ki satyryn kalanyny! */
				right = temp;
				/* System.out.println("Sa?: " + right + "|"); // Kodun sa? kysmyny görmek için commenti kaldyrynç */
				
				if (!is_variable(left)) {
					System.out.println("Erör: Sol taraf de?i?keni hataly!"); 
					one_word = ""; 
					continue; 
				}
				System.out.println("symbol (':=')");				
				is_operation(right);
				one_word = "";
			} else {
				one_word = one_word + girdi.charAt(i);
			}
		}
		if (one_word.trim() != "") System.out.println("Erör: Kodun en sonunda fazlalyk var.");
	}
	
	/**
	 * Gönderilen Stringin geçerli bir variable olup olmady?yny bulur
	 * @param suspect
	 * @return boolean
	 */
	public static boolean is_variable(String suspect) {	
		suspect = suspect.trim();		
		for (int e = 0; e < suspect.length(); e++) {
			if (!is_character(suspect.charAt(e))) return false;
		}
		System.out.println("variable ('" + suspect + "')"); 
		return true;
	}
	
	/**
	 * Gönderilen stringin geçerli bir sa? taraf i?lemi olup olmady?yny bulur.
	 * @param data
	 * @return boolean
	 */
	public static boolean is_operation(String data) {
		
		int index = 0;
		int parantez = 0;
		Vector<String> expected = new Vector<String>();
		
		expected.add("char");
		expected.add("space");
		expected.add("-number");
		expected.add("*");
		expected.add("number");
		expected.add("parantez-ac");

		while (1==1) {
			if (index == data.length()) {
				if (parantez != 0) { System.out.println("Erör: Açyk kalan parantez var."); return false; }
				if (!expected.contains("finish")) { System.out.println("Erör: Komut sonu beklenmiyordu."); return false; }
				System.out.println("symbol (';')"); 
				return true;				
			}
			if (data.charAt(index) == '(' && expected.contains("parantez-ac")) {
				System.out.println("symbol ('(')"); 
				
				parantez++;
				index++;
				expected.clear();
				expected.add("char");
				expected.add("space");
				expected.add("-number");
				expected.add("number");
				expected.add("parantez-ac");
				continue;
			} else if (data.charAt(index) == ')' && expected.contains("parantez-kapa")) {
				parantez--;
				index++;
				if (parantez < 0) { System.out.println("Erör: Parantezler gere?inden fazla kapanmy?."); return false; }
				System.out.println("symbol (')')"); 
				
				expected.clear();
				expected.add("char");
				expected.add("space");
				expected.add("-");
				expected.add("*");
				expected.add("number");
				expected.add("parantez-kapa");
				expected.add("finish");
				continue;
			} else if (is_numeric(data.charAt(index)) && expected.contains("number")) {
				String sayi = "";
				do {
					sayi = sayi + data.charAt(index);
					index++;					
				} while(index < data.length() && is_numeric(data.charAt(index)));
				
				System.out.println("intConstant ('" + sayi + "')"); 
				
				expected.clear();
				expected.add("space");
				expected.add("-");
				expected.add("*");
				expected.add("parantez-kapa");
				expected.add("finish");
				continue;
			} else if ((data.charAt(index) == '-') && expected.contains("-number")) {
				String sayi = "-";
				boolean once = false;
				index++;
				while(index < data.length() && is_numeric(data.charAt(index))) {
					once = true;
					sayi = sayi + data.charAt(index);
					index++;
				}
				
				if (!once) { System.out.println("Erör: - beklenmiyordu."); return false; }
				System.out.println("intConstant ('" + sayi + "')");
				
				expected.clear();
				expected.add("space");
				expected.add("-");
				expected.add("*");
				expected.add("parantez-kapa");
				expected.add("finish");
				continue;	
			} else if (is_character(data.charAt(index)) && expected.contains("char")) {
				String karakter = "";
				do {
					karakter = karakter + data.charAt(index);
					index++;					
				} while(index < data.length() && is_character(data.charAt(index)));
				
				System.out.println("variable ('" + karakter + "')");
				
				expected.clear();
				expected.add("space");
				expected.add("-");
				expected.add("*");
				expected.add("parantez-kapa");
				expected.add("finish");
				continue;				
			} else if ((data.charAt(index) == '-') && expected.contains("-")) {
				System.out.println("symbol ('-')"); 
				index++;

				expected.clear();
				expected.add("space");
				expected.add("number");
				expected.add("char");
				expected.add("parantez-ac");
				continue;
				/* - de?i?ken kabul oluyor ?u notkada. */
			} else if ((data.charAt(index) == '+' || data.charAt(index) == '*') && expected.contains("*")) {
				System.out.println("symbol ('" + data.charAt(index) + "')"); 
				
				index++;
				expected.clear();
				expected.add("space");
				expected.add("number");
				expected.add("char");
				expected.add("parantez-ac");
				continue;
			} else if (data.charAt(index) == ' ' && expected.contains("space")) {
				index++;
				continue;
			} else {
				System.out.println("Erör: Sa? tarafta beklenmeyen karakter. Beklenenler: " + expected.toString()); 
				return false;
			}
		}
	}

	/**
	 * Gönderilen karakterin rakam olup olmady?yny bulur.
	 * @param in
	 * @return boolean
	 */
	public static boolean is_numeric(char in) {
		if (!(in =='1'||in=='2'||in=='3'||in=='4'||in=='5'||in=='6'||in=='7'||in=='8'||in=='9'||in=='0')) return false;
		return true;
	}
	
	/**
	 * Gönderilen karakterin geçerli bir de?i?ken ismi olu?turacak karakter olup olmady?yny döndürür. 
	 * @example (misal _ A B geçerli ama ? ! 2 geçerli de?il.)
	 * @param in
	 * @return boolean
	 */
	public static boolean is_character(char in) {
		if (!(in =='A'||in=='B'||in=='C'||in=='D'||in=='E'||in=='F'||in=='G'||in=='?'||in=='H'||in=='I'||in=='Y'||in=='J'||in=='K'||in=='L'||in=='M'
			||in=='N'||in=='O'||in=='Ö'||in=='P'||in=='R'||in=='S'||in=='?'||in=='T'||in=='U'||in=='Ü'||in=='V'||in=='Y'||in=='Z'||
			
			in =='a'||in=='b'||in=='c'||in=='d'||in=='e'||in=='f'||in=='g'||in=='?'||in=='h'||in=='y'||in=='i'||in=='j'||in=='k'||in=='l'||in=='m'
			||in=='n'||in=='o'||in=='ö'||in=='p'||in=='r'||in=='s'||in=='?'||in=='t'||in=='u'||in=='ü'||in=='v'||in=='y'||in=='z'||in=='_'		
		)) return false;
		return true;
	}
}