package ClassText;

import java.util.Vector;

public class ClassText {

    Vector<String> MainVec = new Vector<>();

    public void addStr(String str) {
        MainVec.add(str);
    }

    public void delStr(int i) {
        if (i >= 0 && i < MainVec.size()) { 
            MainVec.remove(i);
        } else {
            System.out.println("Индекс за пределами размера массива.");
        }
    }

    public void delStr(String str) {
        MainVec.remove(str);
    }

    public void txtInsert(String str, int indx) {
        if (indx >= 0 && indx <= MainVec.size()) { 
            MainVec.ensureCapacity(MainVec.size() + 1);
            MainVec.add(null); 
            for (int i = MainVec.size() - 1; i > indx; i--) {
                MainVec.set(i, MainVec.get(i - 1));
            }
            MainVec.set(indx, str);
        } else {
            System.out.println("Индекс за пределами размера массива.");
        }
    }

    public ClassText clone() {
        ClassText cloned = new ClassText();
        cloned.MainVec.addAll(MainVec);
        return cloned;
    }

    public static boolean compare(ClassText a, ClassText b) {
        return a.MainVec.equals(b.MainVec); 
    }

    public static int wordsCounter(ClassText test_) {
        int counter = 0;
        ClassText test = test_.clone();
        for (int i = 0; i < test.MainVec.size(); i++) {
            String str = test.MainVec.get(i);
            StringBuilder sb = new StringBuilder(str);
            if (str.charAt(0) == ' ') {
                sb.deleteCharAt(0);
            }
            if (str.charAt(str.length() - 1) == ' ') {
                sb.deleteCharAt(str.length() - 1);
            }
            for (int k = 0; k < sb.length(); k++) { 
                if (sb.charAt(k) == ' ') {
                    counter++;
                }
            }
            counter++;
        }
        return counter;
    }

    public static int lettersCounter(ClassText test_) {
        int counter = 0;
        ClassText test = test_.clone();
        for (int i = 0; i < test.MainVec.size(); i++) {
            String str = test.MainVec.get(i);
            String stringWithoutSpaces = str.replaceAll(" ", "");
            counter += stringWithoutSpaces.length(); 
        }
        return counter;
    }

    public static int SentencesCounter(ClassText test_) {
        return test_.MainVec.size();
    }

    public ClassText() {
    }

    public ClassText(String str) {
        this.MainVec.add(str);
    }

    public void Print(ClassText a) {
        if (a.MainVec.isEmpty()) { 
            System.out.println("0");
        }
        for (int i = 0; i < a.MainVec.size(); i++) {
            System.out.println(a.MainVec.get(i));
        }
    }

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
