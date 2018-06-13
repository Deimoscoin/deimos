What is DeiMos?
----------------

DeiMos (DEI) a descentralized global blockchain with a focus on mars colonization and space exploration.

For more information, as well as an immediately useable, binary version of
the DeiMos Core software, see https://deimoscoin.org

DeiMos FAQ
-------------
Total Supply: 1 Billion DeiMos
Block Timing: 30 Second Blocks, (1.5 Minutes per algo)
Mining Algorithims: (Groestl, Skein & Qubit)
Blockchain Type: Public, Decentralized UTXO based
P2P PORT: 9150
RPC PORT: 9149
BlockChain Explorer: https://deimos.network
Deimos Market: https://market.deimoscoin.org (Purchase Deimos using BTC,LTC,DGB)



You can mine DeiMos on one of 4 seperate mining algorithms. Each algo averages out to mine 20% of new blocks. This allows for much greater decentraliztion than other blockchains. In order for an attacker to hardfork DeiMos the attacker would need to control 93% of the hashrate on 1 algo, and 51% of the other 4 making DeiMos much more secure against PoW attacks than other blockchains.

License
-------

DeiMos Core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

Development Process
-------------------

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/deimos/deimos/tags) are created
regularly to indicate new official, stable release versions of DeiMos Core.

The contribution workflow is described in [CONTRIBUTING.md](CONTRIBUTING.md).


Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test on short notice. Please be patient and help out by testing
other people's pull requests, and remember this is a security-critical project where any mistake might cost people
lots of money.

### Automated Testing

Developers are strongly encouraged to write [unit tests](src/test/README.md) for new code, and to
submit new unit tests for old code. Unit tests can be compiled and run
(assuming they weren't disabled in configure) with: `make check`. Further details on running
and extending unit tests can be found in [/src/test/README.md](/src/test/README.md).

There are also [regression and integration tests](/qa) of the RPC interface, written
in Python, that are run automatically on the build server.
These tests can be run (if the [test dependencies](/qa) are installed) with: `qa/pull-tester/rpc-tests.py`

The Travis CI system makes sure that every pull request is built for Windows, Linux, and OS X, and that unit/sanity tests are run automatically.

### Manual Quality Assurance (QA) Testing

Changes should be tested by somebody other than the developer who wrote the
code. This is especially important for large or high-risk changes. It is useful
to add a test plan to the pull request description if testing the changes is
not straightforward.

