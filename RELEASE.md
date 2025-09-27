# Release Procedure

## 1. Update Code & Changelog
- Update `CHANGELOG.md` with the new version and release date
- Commit all changes

## 2. Tag the Release
```bash
git pull origin main
git tag -a v1.0.0 -m "First stable release"
git push origin v1.0.0
