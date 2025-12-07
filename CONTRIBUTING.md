# Contributing to FM56USB Driver Package

Thank you for your interest in contributing to the Gnet FM56USB V.92 56K USB Modem driver package! This document provides guidelines for contributing.

## How to Contribute

### Reporting Issues

If you encounter a problem:

1. **Check Existing Issues**: Search for similar issues before creating a new one
2. **Use Issue Template**: Provide all requested information:
   - Operating system and version
   - Hardware details (modem model, USB port type)
   - Driver version
   - Error messages or symptoms
   - Steps to reproduce
   - What you've already tried

### Suggesting Enhancements

We welcome suggestions for improvements:

1. **Check Roadmap**: Review existing feature requests
2. **Be Specific**: Clearly describe the enhancement and its benefits
3. **Consider Impact**: Think about how it affects existing functionality
4. **Provide Use Cases**: Explain scenarios where this would be helpful

### Code Contributions

#### Getting Started

1. **Fork the Repository**
   ```bash
   # Click "Fork" on GitHub, then clone your fork
   git clone https://github.com/YOUR_USERNAME/Gnet-FM56USB-V.92-56K-USBModem-FULLDRIVER.git
   cd Gnet-FM56USB-V.92-56K-USBModem-FULLDRIVER
   ```

2. **Create a Branch**
   ```bash
   git checkout -b feature/your-feature-name
   # or
   git checkout -b fix/your-bugfix-name
   ```

3. **Make Changes**
   - Follow existing code style
   - Test thoroughly on target platforms
   - Update documentation as needed

4. **Commit Changes**
   ```bash
   git add .
   git commit -m "Brief description of changes"
   ```

5. **Push to Your Fork**
   ```bash
   git push origin feature/your-feature-name
   ```

6. **Create Pull Request**
   - Go to the original repository
   - Click "New Pull Request"
   - Select your branch
   - Provide clear description of changes

#### Code Guidelines

**General Principles:**
- Write clear, maintainable code
- Follow existing coding style
- Add comments for complex logic
- Keep changes focused and minimal
- Test on multiple platforms when possible

**Windows Drivers:**
- Follow Windows Driver Model (WDM) guidelines
- Test on multiple Windows versions
- Ensure compatibility with existing INF files
- Document registry changes

**Linux Kernel Module:**
- Follow Linux kernel coding style
- Test on multiple kernel versions
- Check with `checkpatch.pl` script
- Maintain compatibility with existing systems

**Documentation:**
- Use clear, concise language
- Include examples where appropriate
- Update all affected documentation files
- Check spelling and grammar

#### Testing Requirements

Before submitting:

**Windows Testing:**
- [ ] Driver installs successfully
- [ ] Device Manager shows no errors
- [ ] Modem responds to AT commands
- [ ] Dial-up connection works
- [ ] Tested on at least one Windows version

**Linux Testing:**
- [ ] Module compiles without warnings
- [ ] Module loads successfully
- [ ] Device is detected and creates /dev/ttyACM*
- [ ] Modem responds to AT commands
- [ ] PPP connection works (if applicable)
- [ ] Tested on at least one distribution

**Documentation:**
- [ ] All new features documented
- [ ] README updated if necessary
- [ ] No spelling/grammar errors
- [ ] Links work correctly

### Documentation Contributions

Documentation improvements are highly valuable:

- **Fix Errors**: Typos, broken links, outdated information
- **Add Examples**: Real-world usage examples
- **Improve Clarity**: Rewrite confusing sections
- **Add Languages**: Translations to other languages
- **Expand Coverage**: Add missing topics

#### Documentation Style

- Use Markdown format
- Keep line length reasonable (80-100 characters)
- Use proper heading hierarchy
- Include code blocks with syntax highlighting
- Add links to related sections
- Test all command examples

### Areas for Contribution

We especially welcome contributions in these areas:

**High Priority:**
- Testing on various platforms
- Bug fixes
- Security improvements
- Documentation improvements
- Driver signature for Windows

**Medium Priority:**
- Performance optimizations
- Additional platform support
- GUI utilities
- Automated testing
- Internationalization

**Low Priority:**
- Code refactoring
- Additional examples
- Video tutorials
- Community support

## Development Setup

### Windows Development

**Prerequisites:**
- Windows Driver Kit (WDK)
- Visual Studio
- Virtual machines for testing

**Resources:**
- [Windows Driver Kit Documentation](https://docs.microsoft.com/en-us/windows-hardware/drivers/)
- [Driver Development Best Practices](https://docs.microsoft.com/en-us/windows-hardware/drivers/develop/)

### Linux Development

**Prerequisites:**
```bash
# Ubuntu/Debian
sudo apt-get install build-essential linux-headers-$(uname -r)

# Fedora
sudo dnf install gcc make kernel-devel kernel-headers
```

**Resources:**
- Linux Device Drivers (O'Reilly)
- [Linux Kernel Documentation](https://www.kernel.org/doc/)
- [USB Driver Guide](https://www.kernel.org/doc/html/latest/driver-api/usb/index.html)

## Pull Request Process

1. **Update Documentation**: Ensure README, CHANGELOG, and relevant docs reflect changes
2. **Pass All Tests**: Verify changes work on target platforms
3. **One Feature Per PR**: Keep pull requests focused
4. **Clear Description**: Explain what, why, and how
5. **Respond to Feedback**: Be open to suggestions and revisions
6. **Squash Commits**: Clean up commit history before merging

### Pull Request Template

```markdown
## Description
Brief description of changes

## Type of Change
- [ ] Bug fix
- [ ] New feature
- [ ] Documentation update
- [ ] Performance improvement

## Testing
- [ ] Tested on Windows (versions: ___)
- [ ] Tested on Linux (distros: ___)
- [ ] AT commands work
- [ ] Dial-up connection works

## Checklist
- [ ] Code follows style guidelines
- [ ] Documentation updated
- [ ] No build warnings
- [ ] Tested thoroughly
- [ ] Commit messages are clear
```

## Code Review Process

All contributions go through code review:

1. **Automated Checks**: CI/CD runs automated tests
2. **Maintainer Review**: Core maintainers review changes
3. **Community Feedback**: Other contributors may provide input
4. **Revisions**: Make requested changes
5. **Approval**: Maintainers approve and merge

## Communication

- **GitHub Issues**: Bug reports, feature requests
- **Pull Requests**: Code and documentation changes
- **Discussions**: General questions and ideas

## License

By contributing, you agree that your contributions will be licensed under the same licenses as the project:
- GPL v2 for kernel modules
- Proprietary/GPL compatible for Windows drivers
- CC BY-SA 4.0 for documentation

## Recognition

Contributors are recognized in:
- CHANGELOG.md for significant contributions
- README.md acknowledgments
- Git commit history

## Questions?

If you have questions about contributing:
1. Check existing documentation
2. Search closed issues
3. Open a new issue with [Question] tag
4. Be patient - maintainers are volunteers

## Code of Conduct

### Our Pledge

We are committed to providing a welcoming and inclusive environment for all contributors.

### Expected Behavior

- Be respectful and professional
- Welcome newcomers
- Focus on constructive feedback
- Assume good intentions
- Give credit where due

### Unacceptable Behavior

- Harassment or discrimination
- Trolling or insulting comments
- Personal attacks
- Spam or off-topic content
- Sharing private information

### Enforcement

Violations may result in:
1. Warning
2. Temporary ban
3. Permanent ban

Report issues to project maintainers.

## Thank You!

Your contributions help make this driver package better for everyone. We appreciate your time and effort!
