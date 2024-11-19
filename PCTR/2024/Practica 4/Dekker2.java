/* Copyright (C) 2006 M. Ben-Ari. See copyright.txt */
/* Programmed by Panu Pitk�m�ki */

/* Versión alternativa con bucles finitos */

/* Dekker's algorithm */
class Dekker2 {
    /* Number of processes currently in critical section */
    static volatile int inCS = 0;
    /* Process p wants to enter critical section */
    static volatile boolean wantp = false;
    /* Process q wants to enter critical section */    
    static volatile boolean wantq = false;
    /* Which processes turn is it */
    static volatile int turn = 1;

    class P extends Thread {
        public void run() {
            for (long i = 0; i < 1000000000; i++) {
                /* Non-critical section */
                wantp = true;
                while (wantq) {
                    if (turn == 2) {
                        wantp = false;
                        while (turn == 2)
                            Thread.yield();
                        wantp = true;
                    }
                }
                inCS++;
                Thread.yield();
                /* Critical section */
                System.out.println("Process in critical section: p");
                inCS--;
                turn = 2;
                wantp = false;
            }
        }
    }
    
    class Q extends Thread {
        public void run() {
            for (long i = 0; i < 1000000000; i++) {
                /* Non-critical section */
                wantq = true;
                while (wantp) {
                    if (turn == 1) {
                        wantq = false;
                        while (turn == 1)
                            Thread.yield();
                        wantq = true;
                    }
                }
                inCS++;
                Thread.yield();
                /* Critical section */
                System.out.println("Process in critical section: q");
                inCS--;
                turn = 1;
                wantq = false;
            }
        }
    }

    Dekker2() {
        Thread p = new P();
        Thread q = new Q();
        p.start();
        q.start();
    }

    public static void main(String[] args) {
        new Dekker2();
    }
}