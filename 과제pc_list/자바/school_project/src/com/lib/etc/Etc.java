package com.lib.etc;

public abstract class Etc {
	protected int money;
	
	public abstract int getMoney();
	
	public String getClassName(){
		return this.getClass().getName();
	}

}
