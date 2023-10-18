$$

\begin{align}

[\text{S}] &\to [\text{stmt}]^* 
\\ 
[\text{stmt}] &\to 
\begin{cases}
exit({\text{[expr]}}); \\
let \space \text{ident} = [expr]
\end{cases}
\\
[\text{ident}] &\to [\text{letter}]\space [\text{letter}| \text{int\_lit}]^+
\\
[\text{expr}] &\to \text{int\_lit};
\\
[\text{letter}] &\to [A-Za-Z]^+
\\


\end{align}


$$