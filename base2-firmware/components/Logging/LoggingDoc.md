# Logging Subsystem API

This document provides an overview of the Logging Subsystem, outlining its significance and describing key components. The Logging Subsystem is a vital element within the core of the system, serving as the primary means for various components to communicate by sending generic messages, status updates, error reports, and function results.

## logger.hpp

The `logger.hpp` file contains a class submodule that is accessible to core components.

### Functions in logger.hpp

#### `std::string EVENT_LOG_SDD(void)`

This function, `EVENT_LOG_SDD`, is designed to be periodically executed during a session by an event handler. It is responsible for logging sensor dump data.

#### `std::string EVENT_LOG_SSL(void)`

The `EVENT_LOG_SSL` function is also intended to be periodically executed by the event handler. Its purpose is to log system state information.

#### `std::string EVENT_LOG_SEL(std::string id, mars_exception_t _param1, std::string info)`

The `EVENT_LOG_SEL` function serves a different purpose. It is not run by the event handler but is called only when submodules encounter errors. This function logs detailed error information, including an identifier (`id`), exception type (`mars_exception_t`), and additional information (`info`).

## logtypes.h

The `logtypes.h` file contains various types and values used throughout the logger. It can be included directly or through the `logger.hpp` file.

### mars_exception_t

The `mars_exception_t` struct with a nested `Type` enum and is used to represent exceptions in various log types. It returns two distinct values:

- **ROUTINE_SOFT_FAIL**: Indicates a soft failure under specific conditions.
- **ROUTINE_HARD_FAIL**: Represents a hard failure under specific conditions.

These values help categorize exceptions for logging purposes.

This documentation provides a clear understanding of the Logging Subsystem's structure, functions, and the types it uses for logging and exception handling.
