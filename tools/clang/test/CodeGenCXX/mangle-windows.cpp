// RUN: %clang_cc1 -emit-llvm %s -o - -cxx-abi microsoft \
// RUN:     -triple=i386-pc-win32 | FileCheck --check-prefix=WIN %s
//
// RUN: %clang_cc1 -emit-llvm %s -o - -triple=i386-mingw32 | \
// RUN:     FileCheck --check-prefix=ITANIUM %s

void __stdcall f1(void) {}
// WIN: define x86_stdcallcc void @"\01?f1@@YGXXZ"
// ITANIUM: define x86_stdcallcc void @"\01__Z2f1v@0"

void __fastcall f2(void) {}
// WIN: define x86_fastcallcc void @"\01?f2@@YIXXZ"
// ITANIUM: define x86_fastcallcc void @"\01@_Z2f2v@0"

extern "C" void __stdcall f3(void) {}
// WIN: define x86_stdcallcc void @"\01_f3@0"
// ITANIUM: define x86_stdcallcc void @"\01_f3@0"

extern "C" void __fastcall f4(void) {}
// WIN: define x86_fastcallcc void @"\01@f4@0"
// ITANIUM: define x86_fastcallcc void @"\01@f4@0"

struct Foo {
  void __stdcall foo();
  static void __stdcall bar();
};

void Foo::foo() {}
// WIN: define x86_stdcallcc void @"\01?foo@Foo@@QAGXXZ"
// ITANIUM: define x86_stdcallcc void @"\01__ZN3Foo3fooEv@4"

void Foo::bar() {}
// WIN: define x86_stdcallcc void @"\01?bar@Foo@@SGXXZ"
// ITANIUM: define x86_stdcallcc void @"\01__ZN3Foo3barEv@0"

// Mostly a test that we don't crash and that the names start with a \01.
// gcc on mingw produces __Zpp@4
// cl produces _++@4
extern "C" void __stdcall operator++(Foo &x) {
}
// WIN: define x86_stdcallcc void @"\01??E@YGXAAUFoo@@@Z"
// ITANIUM: define x86_stdcallcc void @"\01__ZppR3Foo@4"
