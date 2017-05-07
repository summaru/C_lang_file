package main;

import java.util.Scanner;

import com.lib.DataBase;
import com.lib.SystemUtil;

public class Main {
	
	
	public static void main(String []args){
		DataBase db = new DataBase();
		
		while(true){
			System.out.println("Pc방 회원 관리 리스트");
			System.out.println("1.회원가입");
			System.out.println("2.로그인");
			System.out.println("3.로그아웃");
			System.out.println("4.기타구매");
			System.out.println("5.회원리스트");
			System.out.println("6.pc리스트");
			System.out.println("7.종료");
			System.out.print("입력>>");
			Scanner scan = new Scanner(System.in);
			int cho = scan.nextInt();
			switch(cho){
			case 1:
				db.signUp();
				break;
			case 2:
				db.signIn();
				break;
			case 3:
				db.signOut();
				break;
			case 4:
				db.payEtc();
				break;
			case 5:
				db.viewUserList();
				break;
			case 6:
				db.viewPcList();
				break;
			case 7:
				System.exit(0);
				break;
			default:
				System.out.print("재입력");
				SystemUtil.threeSencondCls();
				break;
			}
			
		}
		
	}
}
