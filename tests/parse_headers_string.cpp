#include "testing_header.hpp"

TEST_CASE("Trying parse_headers_string with single line") {
	auto const headers = http::algorithms::parse_headers_string("Last-Modified: tomorrow at 4 am");

	REQUIRE(headers.size() == 1);
	CHECK(headers[0] == http::Header{.name="Last-modified", .value="tomorrow at 4 am"});
}

TEST_CASE("Trying parse_headers_string with multiple lines") {
	auto const headers = http::algorithms::parse_headers_string(
R"(


One: aaa
Two: bbbbbbb
Three: ccccccc

Last-Modified: tomorrow at 4 am

)"
	);
	constexpr auto expected = std::array{
		http::Header{.name="oNe", .value="aaa"},
		http::Header{.name="TwO", .value="bbbbbbb"},
		http::Header{.name="thRee", .value="ccccccc"},
		http::Header{.name="last-modified", .value="tomorrow at 4 am"},
	};

	CHECK(std::ranges::equal(headers, expected));
}

TEST_CASE("Trying parse_headers_string with multiple lines without any valid headers") {
	auto const headers = http::algorithms::parse_headers_string(
R"(
One ~ aaa
Two....... bbbbbbb

Three!! ccccccc


Last-Modified - tomorrow at 4 am
)"
	);
	CHECK(headers.empty());
}

TEST_CASE("Trying parse_headers_string with empty string") {
	CHECK(http::algorithms::parse_headers_string("").empty());
}
