package main;

import java.util.Scanner;

import com.lib.DataBase;
import com.lib.SystemUtil;

public class Main {
	
	
	public static void main(String []args){
		DataBase db = new DataBase();
		
		while(true){
			System.out.println("Pc�� ȸ�� ���� ����Ʈ");
			System.out.println("1.ȸ������");
			System.out.println("2.�α���");
			System.out.println("3.�α׾ƿ�");
			System.out.println("4.��Ÿ����");
			System.out.println("5.ȸ������Ʈ");
			System.out.println("6.pc����Ʈ");
			System.out.println("7.����");
			System.out.print("�Է�>>");
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
				System.out.print("���Է�");
				SystemUtil.threeSencondCls();
				break;
			}
			
		}
		
	}
}
