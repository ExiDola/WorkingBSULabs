package test;

import ClassText.ClassText;

public class test extends ClassText
{
	public static void main(String[] args) {
        ClassText a = new ClassText();
        a.addStr("aaa");
        a.Print(a);
        a.delStr(0);
        a.Print(a);
        a.txtInsert("bbb", 0);
        a.Print(a);
        ClassText b = new ClassText();
        b.addStr("ccc");
        if (compare(a, b)) {
            System.out.println("равны");
        } else {
            System.out.println("не равны");
        }

        System.out.println(lettersCounter(a));
        System.out.println(wordsCounter(a));
        System.out.println(SentencesCounter(a));
    }
}
