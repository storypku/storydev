# Demo Project to Separate Lint Tests from Unit Tests

## To Run All Lint Tests

```
bazel test --config=lint //...
```

## To Run All Unit Tests

```
bazel test --config=nolint <your-bazel-targets>
```

## To Run All Benchmarks

```
bazel run --config=bm //...
```

**Notes**
> This depends on the relavent `cc_binary` rule having a "benchmark" tag.
> Maybe we should define a `benchmark` rule to simplify that.

## Known Issues
1. Cpplint for benchmarks will fail as use of non const reference parameter
   violates google coding style. See
   [Ref](https://github.com/google/benchmark/issues/394)

   We have to add a trailing `// NOLINT` comment at each `BM_` function defination.
