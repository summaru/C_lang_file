package com.lib;

import java.io.IOException;

public class SystemUtil {
	
	public static final long startTime = (System.nanoTime()/1000000000);
	
	private SystemUtil(){
		
	}
	
	private static void clearCmd(){
		ProcessBuilder pb = new ProcessBuilder("cmd","/c","cls");
		try {
			pb.inheritIO().start();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		pb = null;
		
	}
	
	public static long getCurrentSecond(){
		return (System.nanoTime()/1000000000)-startTime;
	}
	
	public static void delay(){
		try {
			Thread.sleep(1500);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public static void threeSencondCls(){
		delay();
		clearCmd();
		delay();
	}
	
	public static long operatorHour(long time){
		long ret = time/3600;
		
		if (time % 3600 != 0){
			ret += 1;
		}
		return ret;
	}
	
	
	
}
