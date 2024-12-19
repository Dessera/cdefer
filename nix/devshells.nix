{ self', pkgs, ... }:
ccenv:
let
  target = rec {
    inputsFrom = [ self'.packages.default ];

    packages = with pkgs; [
      nixd
      nixfmt-rfc-style
      mesonlsp
      clang-tools
    ];

    CPATH =
      "${ccenv.cc.libc.dev}/include:"
      + "${ccenv.cc.cc}/lib/gcc/x86_64-unknown-linux-gnu/${ccenv.cc.version}/include";
    C_INCLUDE_PATH = CPATH;
    CPLUS_INCLUDE_PATH =
      "${ccenv.cc.cc}/include/c++/${ccenv.cc.version}:"
      + "${ccenv.cc.cc}/include/c++/${ccenv.cc.version}/x86_64-unknown-linux-gnu:"
      + CPATH;
  };
in
{
  default = pkgs.mkShell.override {
    stdenv = ccenv;
  } target;
}
