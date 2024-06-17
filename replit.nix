{ pkgs }:

let
  Process = pkgs.stdenv.mkDerivation {
    name = "Process";
    src = ./codigo;  # Diretório contendo o código fonte
    buildInputs = [ pkgs.gcc pkgs.gnumake ];  # Dependências necessárias para a construção

    buildPhase = ''
      gcc -c Process.c -o Process.o  # Compila o arquivo Process.c em um objeto
      ar rcs libProcess.a Process.o  # Cria uma biblioteca estática a partir dos objetos
    '';

    installPhase = ''
      mkdir -p $out/lib $out/include  
      cp libProcess.a $out/lib/  
      cp Process.h $out/include/  
    '';
  };

  Main = pkgs.stdenv.mkDerivation {
    name = "Main";
    src = ./codigo;  # Diretório contendo o main.c
    buildInputs = [ pkgs.gcc pkgs.gnumake Process ];  # Inclui a biblioteca Process como dependência

    buildPhase = ''
      gcc -I${Process}/include -L${Process}/lib -lProcess main.c -o main  
    '';

    installPhase = ''
      mkdir -p $out/bin
      cp main $out/bin/
    '';
  };

in
{
  exports = {
    default = Main;  # Exporta a derivação Main como padrão
  };

  deps = [
    Process
    Main
  ];
}
