# Swordfish
## English dictionary for Sailfish OS

Lookup definitions, examples and related words.

Swordfish uses the [Wordnik](https://wordnik.com) [API](http://developer.wordnik.com). If you want to
support Wordnik, you can [adopt your favourite word](https://www.wordnik.com/adoptaword).

### Building the project

To compile and use this project you will need a Wordnik API key. First register at [Wordnik](https://wordnik.com),
then apply for a key at [their developer site](http://developer.wordnik.com).

Once approved, you can find your key at your [profile page](https://wordnik.com/users/edit).

To use it in the project add a file called `apikey.pro` to the root of the project (same directory
as `harbour-swordfish.pro`):

In that file write: `DEFINES += API_KEY=\"\\\"YOUR_API_KEY\\\"\"`, where `YOUR_API_KEY` of
course is your API key ;)