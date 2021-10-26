cronometro c;
long int r = 0;
const double e_abs = 0.01, // Máximo error absoluto cometido.
e_rel = 0.001; // Máximo error relativo aceptado.
c.activar();
do {
// ... fragmento a cronometrar ...
++r;
} while (c.tiempo() < e_abs / e_rel + e_abs);
c.parar();
double t = c.tiempo() / r;