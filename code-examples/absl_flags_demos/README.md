# Absl flags by Example

This project was primarily the code examples illustrating the
[Absl Flags C++ Guide](https://abseil.io/docs/cpp/guides/flags)

## Best Practises for Absl Flags

1. All flags should be defined outside any C++ namespace.

    By doing so, if multiple definitions of flags with the same name are linked into a
    single program the linker will report an error.

2. Avoid flags, especially in library code

   The necessity to access flags from different files, especially in libraries,
   is generally a sign of a bad design. Given the "global variable" nature of
   flags they should be avoided in libraries and be injected instead (e.g. in
   constructors). (see https://abseil.io/tips/45)

3. https://abseil.io/docs/cpp/guides/flags#best-practices-for-defining-custom-flag-types

4. https://abseil.io/docs/cpp/guides/flags#flags-best-practices
   For example,
    - Do not declare any flags that you do not own yourself.
    - Do not access a binary’s flags within any tight loops. Flags are expensive to read.

## About the examples

1. Only recent releases of Abseil provides flag support for absolute time values. Namely,
`absl::Duration` and `absl::Time`

2. As `glog` can either work w/ and w/o dependency on `gflags`. In order to deprecate `gflags` globally,
   we choose `glog` w/o `gflags` support. See `third_party/glog/glog.BUILD`.




